package javagame;

import java.util.Random;

public abstract class Enemy extends Npc{

	Random random = new Random();
	
	Enemy(){
		  randy=768/2;
	      randx=1400;
	      x=1400;
	      y=768/2;
	}
	
	public abstract void ReHealth();
	
	public void movement(){

		//random = new Random();
		if(Math.abs(randx-x)<=movementspeed)
        {
            randx = random.nextInt(1366-20) + 20;
        }
        if(Math.abs(randy-y)<=movementspeed)
        {
            randy = random.nextInt(768-15) + 15;
        }

        if(randx<x)
        {
            x=x-movementspeed;
        }
        if(randx>x)
        {
            x=x+movementspeed;
        }
        if(randy>y)
        {
            y=y+movementspeed;
        }
        if(randy<y)
        {
            y=y-movementspeed;
        }


      /*  if(x<20)
        {
            x=oldx;
        }
        if(y<15 || y>768-15)
        {
            y=oldy;
        }
        */

        if(oldx==x)
        {
            randx = random.nextInt(1366-20) + 20;
        }
        if(oldy==y)
        {
            randy = random.nextInt(768-15) + 15;
        }
        oldx=x;
        oldy=y;
	}

	public int ID;
	private int randy;
	private int randx;
}
