difference(){
    
    union(){    
        linear_extrude (height=3)
            import (file="chassis.dxf", layer="chassis", $fn=100);
        
        
        //pates de fixation des moteurs
        translate ([0,0,2.99])
            linear_extrude (height=25)
            import (file="chassis.dxf", layer="chassis-fixation-moteur", $fn=100);
      
        
    
       
  //fixation 3ème roue
  hull(){    
      
              translate ([0,0,2.99])
            linear_extrude (height=1)
            import (file="chassis.dxf", layer="3emeRoueG", $fn=100);
        
        translate ([18.5,-75.8,23])
            sphere(r=1.5, $fn=50);
        }
        
         hull(){    
            translate ([0,0,2.99])
            linear_extrude (height=1)
            import (file="chassis.dxf", layer="3emeRoueD", $fn=100);
        translate ([31.5,-75.8,23])
            sphere(r=1.5, $fn=50);
        }
    }
    
   
   union(){
       
       //trous pour les vis
       translate([-50,38.8,5.5])
       rotate([0,90,0])
        #cylinder(h = 150, r1 = 1.5, r2 = 1.5, center = true/false, $fn=100);
       
       translate([-50,38.8, 23])
       rotate([0,90,0])
        #cylinder(h = 150, r1 = 1.5, r2 = 1.5, center = true/false, $fn=100);
     
      
       //14.25
              translate([-50,-75.8, 18])
       rotate([0,90,0])
        #cylinder(h = 150, r1 = 1.5, r2 = 1.5, center = true/false, $fn=100);
   }
   
}
   