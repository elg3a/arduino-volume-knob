
L = 54;
H = 30;
wall = 1.2;
r = 34/2;
open = 30;


difference() {
    cube([L,L,H]);
    translate([wall, wall, 0] ) {
        cube([L-2*wall, L-2*wall, H-15+wall]);
    }
    translate([2*wall, 2*wall, 0] ) {
        cube([L-4*wall, L-4*wall, H-wall]);
    }
    // knob
    translate([L/2,L/2,H-wall]) {
        cylinder(wall, r, r, $fn=50);
    }
    // usb
    translate([0, wall+1.5, 13]) {
        cube([wall, 2.5, 7.5]);
    }
}


translate([0, 0, -open]) {
    // base
    cube([L, L, wall]);
    difference() {
        translate([wall,wall,wall]) {
            cube([L-2*wall, L-2*wall, 2*wall]);
        }
        translate([2*wall,2*wall,wall]) {
            cube([L-4*wall, L-4*wall, 2*wall]);
        }
    }


    // holder
    translate([wall, L/2-10, 13]) {
        difference() {
            cube([L-2*wall, 20, 2*wall]);
            //large
            translate([(L-2*wall)/2, 10, 0]) {
                cylinder(3*wall, 4.5, 4.5, $fn=30);
            }
            // small
            translate([(L-2*wall)/2+7, 10, 0]) {
                cylinder(3*wall, 1.5, 1.5, $fn=20);
            }
        }
    }
}

// ard
translate([wall,wall,-open+7]) {
    cube([33,1.5,19]);
    translate([-3,1.5,6]) {
        cube([6,2.5,7.7]);
    }
}