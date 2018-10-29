difference(){
    
    union(){
        linear_extrude (height=3)
            import (file="chassis.dxf", layer="chassis", $fn=100);
        translate ([0,0,2.99])
            linear_extrude (height=25)
            import (file="chassis.dxf", layer="chassis-fixation-moteur", $fn=100);  
    }
   union(){
       translate([-50,38.8,5.2])
       rotate([0,90,0])
        cylinder(h = 150, r1 = 1.5, r2 = 1.5, center = true/false, $fn=100);
       
       translate([-50,38.8,23.2])
       rotate([0,90,0])
        cylinder(h = 150, r1 = 1.5, r2 = 1.5, center = true/false, $fn=100);
   }
}
   