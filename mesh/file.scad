// --- PARAMETERS ---
torso_height = 40;
head_radius = 10;
limb_radius = 3;
limb_length = 35;

// --- ASSEMBLY ---
// The final model is assembled using the union() function
union()
{
    // 1. Torso (Main Body)
    color([0.8, 0.6, 0.4]) // Skin tone color for visualization
    {
        translate([0, 0, 0])
        {
            cylinder(h = torso_height, r = head_radius * 0.7, $fn = 20);
        }
    }

    // 2. Head (Sphere on top)
    color([0.8, 0.6, 0.4])
    {
        translate([0, 0, torso_height + head_radius])
        {
            sphere(r = head_radius, $fn = 30);
        }
    }

    // 3. Right Arm
    color([0.5, 0.5, 0.5]) // Gray for clothes visualization
    {
        // Start position for the arm relative to the top of the torso
        translate([head_radius * 0.7, 0, torso_height - limb_radius])
        {
            // Rotate the arm slightly down (e.g., -15 degrees around the Y-axis)
            rotate([0, -15, 0])
            {
                // Use hull() to create a smooth connection from the shoulder sphere to the wrist sphere
                hull()
                {
                    // Shoulder joint (a sphere)
                    sphere(r = limb_radius * 1.5, $fn = 12);
                    
                    // Wrist position (a sphere)
                    translate([limb_length, 0, 0])
                    {
                        sphere(r = limb_radius, $fn = 12);
                    }
                }
            }
        }
    }

    // 4. Left Arm (Mirror of the Right Arm, moved to the negative X side)
    color([0.5, 0.5, 0.5])
    {
        translate([-head_radius * 0.7, 0, torso_height - limb_radius])
        {
            rotate([0, 15, 0])
            {
                hull()
                {
                    sphere(r = limb_radius * 1.5, $fn = 12);
                    translate([-limb_length, 0, 0]) // Note the negative X translation
                    {
                        sphere(r = limb_radius, $fn = 12);
                    }
                }
            }
        }
    }
    
    // 5. Legs (Simplified Cylinders)
    color([0.3, 0.3, 0.7]) // Blue for pants visualization
    {
        // Right Leg
        translate([limb_radius, 0, 0])
        {
            cylinder(h = limb_length, r = limb_radius * 1.5, $fn = 12);
        }

        // Left Leg
        translate([-limb_radius, 0, 0])
        {
            cylinder(h = limb_length, r = limb_radius * 1.5, $fn = 12);
        }
    }
}
