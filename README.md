# Braço Robótico de Coleta de Amostras
### Docking & Retrieval — Missão Microgravidade

> Projeto de robótica espacial com Arduino Uno: braço robótico controlado via Monitor Serial com 2 servomotores SG90 e LED de status. Inclui simulação no Tinkercad e modelo 3D paramétrico da garra em OpenSCAD.

---

## Link

**Simulador Tinkercad** | https://www.tinkercad.com/things/cqUtWiq2RES-braco-robotico-gs/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard&sharecode=oAwwiPhLlkZ0bLWyZTrHQUvW-zTJaHNb8wejktAVEA4

---

## Estrutura do Repositório

```
braco-robotico/
│
├── code/
│   └── robotic_arm_tinkercad.ino   # Código Arduino — controle dos servos
│
├── model/
│   ├── GS2026.scad           # Exportação para impressão 3D
│
├── images/
│   └── Print1          # Render do modelo 3D
│   └── Print2
│   └── Print3
│   └── Print4
│
└── README.md
```

---

## Componentes

| Componente | Qtd | Observação |
|---|---|---|
| Arduino Uno R3 | 1 | — |
| Servo Motor SG90 (9g) | 2 | Ombro + Garra |
| LED 5mm | 1 | Qualquer cor — indicador de status |
| Resistor 220 Ω | 1 | Em série com o LED |
| Protoboard | 1 | — |
| Jumpers | ~15 | Macho-Macho / Macho-Fêmea |
| Fonte de alimentação | 1 | **6V** — alimenta os servos |

---

## Esquema de Ligação

```
FONTE DE ALIMENTAÇÃO (6V)
  (+) ────────── Barramento + da protoboard ────── VCC dos servos
  (–) ────────── Barramento – da protoboard ────── GND dos servos

ARDUINO UNO
  Pino  9  ──── Sinal (fio laranja) ──── Servo OMBRO
  Pino 10  ──── Sinal (fio laranja) ──── Servo GARRA
  Pino 13  ──── Resistor 220Ω ──── Ânodo (+) do LED ──── GND
  GND      ──── Barramento – da protoboard  ← GND COMUM (obrigatório)
```

> O GND do Arduino e o GND da fonte **devem estar no mesmo barramento** da protoboard. Sem isso os servos não respondem.

### Tabela de pinos

| Componente | Pino Arduino | Tipo de sinal |
|---|---|---|
| Servo Ombro | 9 | PWM |
| Servo Garra | 10 | PWM |
| LED Status | 13 | Digital Output |

---

## Como usar no Tinkercad

### 1. Iniciar a simulação

1. Clique em **Iniciar simulação**
2. Clique na aba **Monitor Serial** (rodapé da tela)
3. Configure o baud rate para **9600**
4. A mensagem de boas-vindas confirma que está funcionando:

### 2. Comandos disponíveis

| Comando | Ação |
|---|---|
| `U` | Ombro vai para **cima** |
| `D` | Ombro vai para **baixo** |
| `O` | Garra **abre** |
| `C` | Garra **fecha** — captura a amostra | 

> O sistema aceita letras minúsculas e maiúsculas.

### 3. Sequência de missão (captura de amostra)

```
1. D  →  Desce o braço até a amostra
2. O  →  Abre a garra
3. C  →  Fecha a garra — AMOSTRA CAPTURADA
4. U  →  Sobe o braço com a amostra
```

---

## LED de status

| Padrão | Significado |
|---|---|
| Aceso contínuo | Sistema pronto |
| 1 piscada | Comando executado (U, M, D, O) |
| 2 piscadas | Garra fechou — captura confirmada |
| 3 piscadas | Comando inválido |

---

## Modelo 3D — Garra Paramétrica


## 📸 Imagens

### Circuito simulado — Tinkercad

<img width="1090" height="1022" alt="image" src="https://github.com/user-attachments/assets/2a140f61-5963-4aaa-a0ee-1d74018206cd" />

<img width="2549" height="1250" alt="image" src="https://github.com/user-attachments/assets/67b13889-819c-4f77-9e1f-11b8621c8f4a" />

### Modelo 3D — Garra


## Autores

João Rodrigo Solano Nogueira RM 551319 
Julia Amorim Bezerra RM 99609 
Lana Giulia Auada Leite  RM 551143 
Tony Willian da Silva Segalin RM 550667


