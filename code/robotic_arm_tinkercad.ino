#include <Servo.h>

// ── Pinos ────────────────────────────────────────────────────
#define PINO_OMBRO 9
#define PINO_GARRA 10
#define PINO_LED   13

// ── Angulos ──────────────────────────────────────────────────
#define OMBRO_MIN    0
#define OMBRO_MAX  180
#define OMBRO_HOME  90
#define GARRA_ABRE  60
#define GARRA_FECHA 10
#define PASSO       15
#define VEL         15

// ── Objetos e estado ─────────────────────────────────────────
Servo servoOmbro;
Servo servoGarra;

int posOmbro = OMBRO_HOME;
int posGarra = GARRA_ABRE;

// ── Move o servo do OMBRO suavemente ─────────────────────────
void moverOmbro(int alvo) {
  int passo = (alvo > posOmbro) ? 1 : -1;
  while (posOmbro != alvo) {
    posOmbro += passo;
    servoOmbro.write(posOmbro);
    delay(VEL);
  }
}

// ── Move o servo da GARRA suavemente ─────────────────────────
void moverGarra(int alvo) {
  int passo = (alvo > posGarra) ? 1 : -1;
  while (posGarra != alvo) {
    posGarra += passo;
    servoGarra.write(posGarra);
    delay(VEL);
  }
}

// ── Pisca o LED N vezes ───────────────────────────────────────
void piscarLED(int vezes, int ms) {
  for (int i = 0; i < vezes; i++) {
    digitalWrite(PINO_LED, LOW);
    delay(ms);
    digitalWrite(PINO_LED, HIGH);
    delay(ms);
  }
}

// ── Exibe status no Serial ────────────────────────────────────
void exibirStatus() {
  Serial.println("--- STATUS ---");
  Serial.print("Ombro: "); Serial.print(posOmbro); Serial.println(" graus");
  Serial.print("Garra: "); Serial.print(posGarra);
  Serial.println(posGarra <= 15 ? " graus [FECHADA]" : " graus [ABERTA]");
  Serial.println("--------------");
}

// ── Retorna ao HOME ───────────────────────────────────────────
void irHome() {
  Serial.println("[H] Indo para HOME...");
  moverOmbro(OMBRO_HOME);
  moverGarra(GARRA_ABRE);
  Serial.println("[H] HOME concluido.");
  piscarLED(2, 150);
}

// ─────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);

  pinMode(PINO_LED, OUTPUT);
  digitalWrite(PINO_LED, HIGH);

  servoOmbro.attach(PINO_OMBRO);
  servoGarra.attach(PINO_GARRA);

  servoOmbro.write(OMBRO_HOME);
  servoGarra.write(GARRA_ABRE);
  delay(800);

  Serial.println("=========================================");
  Serial.println(" BRACO ROBOTICO ESPACIAL - MISSAO ZERO  ");
  Serial.println("=========================================");
  Serial.println(" U -> Ombro SOBE   (+15 graus)");
  Serial.println(" D -> Ombro DESCE  (-15 graus)");
  Serial.println(" O -> Garra ABRE");
  Serial.println(" C -> Garra FECHA  (captura amostra)");
  Serial.println(" H -> HOME");
  Serial.println(" S -> Status");
  Serial.println("-----------------------------------------");
  Serial.println("Pronto. Digite um comando:");
}

// ─────────────────────────────────────────────────────────────
void loop() {
  if (Serial.available() > 0) {

    char cmd = (char)Serial.read();

    if (cmd == '\n' || cmd == '\r' || cmd == ' ') return;

    cmd = toupper(cmd);
    Serial.print("[CMD] "); Serial.println(cmd);

    switch (cmd) {

      case 'U':
        if (posOmbro + PASSO <= OMBRO_MAX) {
          moverOmbro(posOmbro + PASSO);
          Serial.print("[U] Ombro: "); Serial.print(posOmbro); Serial.println(" graus");
          piscarLED(1, 80);
        } else {
          Serial.println("[!] Limite maximo atingido (180 graus)");
          piscarLED(3, 180);
        }
        break;

      case 'D':
        if (posOmbro - PASSO >= OMBRO_MIN) {
          moverOmbro(posOmbro - PASSO);
          Serial.print("[D] Ombro: "); Serial.print(posOmbro); Serial.println(" graus");
          piscarLED(1, 80);
        } else {
          Serial.println("[!] Limite minimo atingido (0 graus)");
          piscarLED(3, 180);
        }
        break;

      case 'O':
        Serial.println("[O] Abrindo garra...");
        moverGarra(GARRA_ABRE);
        Serial.println("[O] Garra ABERTA (60 graus)");
        piscarLED(1, 80);
        break;

      case 'C':
        Serial.println("[C] Fechando garra...");
        moverGarra(GARRA_FECHA);
        Serial.println("[C] AMOSTRA CAPTURADA! (10 graus)");
        piscarLED(2, 150);
        break;

      case 'H':
        irHome();
        break;

      case 'S':
        exibirStatus();
        break;

      default:
        Serial.println("[!] Comando invalido. Use: U D O C H S");
        piscarLED(3, 180);
        break;
    }

    digitalWrite(PINO_LED, HIGH);
  }
}
