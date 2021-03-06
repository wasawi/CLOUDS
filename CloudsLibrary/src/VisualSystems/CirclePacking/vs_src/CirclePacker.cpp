//
//  CirclePacker.cpp
//  CirclePacking
//
//  Created by Jonathan Minard on 12/9/13.
//
//

#include "CirclePacker.h"


CirclePacker::CirclePacker()
{
	width = height = padding = xcenter = ycenter = 0; 
    damping =  iterations  = 0;    
}

CirclePacker::CirclePacker(float _width, float _height, float _padding)
{
    width = _width;
    height = _height;
    xcenter = width/2;
    ycenter = height/2;
    padding = _padding;
    damping = 0.001;
    iterations = 1;
}

float CirclePacker::fast_distance(float _x1, float _y1, float _x2, float _y2)
{
    return (_x1 - _x2) * (_x1 - _x2) + (_y1 - _y2) * (_y1 - _y2);
}

void CirclePacker::pack()
{
    if(circles.size()>2){
		for (list<Circle>::iterator i = circles.begin(); i != circles.end(); i++)
		{
			Circle& c1 = *i;
        
			for (list<Circle>::iterator j = i; j != circles.end(); j++)
			{
				Circle& c2 = *j;   // Circle& c2 = circles[j]
            
				float d = fast_distance(c1.x, c1.y, c2.x, c2.y);
				float r = c1.r + c2.r + padding;
            
				if (d > 0 && d < (r*r))
				{
					float dx = c2.x - c1.x;
					float dy = c2.y - c1.y;
					float droot = sqrt(d);
					                
					// proviamo a dare un peso rispetto al centro
					float cd1 = ofDistSquared(c1.x, c1.y, xcenter, ycenter);
					float cd2 = ofDistSquared(c1.x, c1.y, xcenter, ycenter);
					
					float total = dx + dy;
					float vx = (dx/droot) * (r-droot);
					float vy = (dy/droot) * (r-droot);
                
					c1.x -= vx * cd1/(cd1+cd2) * ofMap(c1.r, 100., 0., .3, 1., true);
					c1.y -= vy * cd1/(cd1+cd2) * ofMap(c1.r, 100., 0., .3, 1., true);
					c2.x += vx * cd2/(cd1+cd2) * ofMap(c2.r, 100., 0., .3, 1., true);
					c2.y += vy * cd2/(cd1+cd2) * ofMap(c2.r, 100., 0., .3, 1., true);
				}
			}
		}
    }
    
    // contraction...
    //

    for (list<Circle>::iterator i = circles.begin(); i != circles.end(); i++) {
		 Circle& c = *i;
		 float vx = (c.x - xcenter) * damping;
		 float vy = (c.y - ycenter) * damping;
		 c.x -= vx;
		 c.y -= vy;
     }
}

void CirclePacker::update() {
    for(int w=0; w<iterations; w++){
        this->pack();
    }
}

/**
 * Draw all the circles
 */
void CirclePacker::draw(bool _nasdaq, bool _blanks, bool _hashtags)
{
    if (_blanks){
        for (list<Circle>::iterator i = circles.begin();i != circles.end(); i++){
			Circle& c = *i;
			if (c.r < 4){
				circles.erase(i);
				break;
			}
        }

		for (list<Circle>::iterator i = circles.begin();i != circles.end(); i++){
			Circle& c = *i;
			c.draw();
        }
	}
    
    if (_nasdaq){
        for (list<Circle>::iterator i = circles.begin();i != circles.end(); i++){
            Circle& c = *i;
            if (c.r < 1){
                circles.erase(i);
				break;
            }
		}

        for (list<Circle>::iterator i = circles.begin();i != circles.end(); i++){
            Circle& c = *i;
            c.drawCompanies();
        }
    }
    
    
    if (_hashtags){
        for (list<Circle>::iterator i = circles.begin(); i != circles.end(); i++){
            Circle& c = *i;
            if (circles.size() > 25){
                Circle& b = *(circles.begin());
                b.r -= .5;
            }
            if (c.r < 1){
				circles.erase(i);
				break;
            }
        }
 
		for (list<Circle>::iterator i = circles.begin(); i != circles.end(); i++){
            Circle& c = *i;
            c.drawHashtags();
		}
    }
}

