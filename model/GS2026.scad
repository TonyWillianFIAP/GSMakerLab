// ======================================================
// GARRA ESPACIAL PARAMÉTRICA
// Global Solution 2026 - PBML
// ======================================================

// ---------- PARÂMETROS ----------

finger_length = 45;
finger_width  = 8;
finger_height = 6;

palm_width  = 40;
palm_depth  = 18;
palm_height = 12;

opening = 18;

servo_hole = 3;

$fn = 64;


// ---------- DEDO ----------

module finger() {

    difference() {

        union() {

            // Corpo principal
            cube([
                finger_width,
                finger_length,
                finger_height
            ]);

            // Ponta curva
            translate([
                finger_width/2,
                finger_length,
                finger_height/2
            ])
            sphere(r=4);
        }

        // Janela de alívio de massa
        translate([
            2,
            10,
            -1
        ])
        cube([
            finger_width-4,
            18,
            finger_height+2
        ]);

        // Cavidade de captura
        translate([
            finger_width/2,
            finger_length-2,
            finger_height/2
        ])
        sphere(r=2);
    }
}


// ---------- PALMA ----------

module palm() {

    difference() {

        cube([
            palm_width,
            palm_depth,
            palm_height
        ]);

        // Furo esquerdo
        translate([
            palm_width/2-7,
            palm_depth/2,
            -1
        ])
        cylinder(
            d=servo_hole,
            h=palm_height+2
        );

        // Furo direito
        translate([
            palm_width/2+7,
            palm_depth/2,
            -1
        ])
        cylinder(
            d=servo_hole,
            h=palm_height+2
        );

        // Janela lateral esquerda
        translate([
            3,
            3,
            2
        ])
        cube([
            6,
            palm_depth-6,
            palm_height-4
        ]);

        // Janela lateral direita
        translate([
            palm_width-9,
            3,
            2
        ])
        cube([
            6,
            palm_depth-6,
            palm_height-4
        ]);
    }
}


// ---------- PINO DE MONTAGEM ----------

module mount() {

    translate([
        palm_width/2,
        -5,
        palm_height/2
    ])

    rotate([90,0,0])

    cylinder(
        d=8,
        h=10
    );
}


// ---------- MONTAGEM FINAL ----------

module gripper() {

    palm();

    mount();

    // Dedo esquerdo
    translate([
        palm_width/2-opening/2-finger_width,
        palm_depth,
        3
    ])
    finger();

    // Dedo direito
    translate([
        palm_width/2+opening/2+finger_width,
        palm_depth,
        3
    ])
    mirror([1,0,0])
    finger();
}

gripper();