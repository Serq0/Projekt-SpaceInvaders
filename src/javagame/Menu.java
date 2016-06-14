package javagame;

import org.lwjgl.input.Mouse;
import org.newdawn.slick.*;
import org.newdawn.slick.state.*;

public class Menu extends BasicGameState{
	
	public String mouse = "No input";
	//Image sword;
	Image menu;
	Image graj;
	Image wyjscie;
	
	
	public Menu(int state){
		
	}
	
	public void init(GameContainer gc, StateBasedGame sbg)throws SlickException{
		//sword = new Image ("res/sword.gif");
		menu = new Image("res/menu.bmp");
		graj = new Image("res/graj.png");
		wyjscie = new Image("res/wyjscie.png");
	}
	
	public void render(GameContainer gc, StateBasedGame sbg, Graphics g)throws SlickException{
		
		//g.drawRect(50, 100, 60, 120); //rysowanie prostokatow
		//g.drawOval(200, 130, 130, 80); // rysowanie kol
		g.drawImage(menu, 0, 0);
		
		//g.drawRect(1366/2-100,768/2,200,50);
		//g.drawRect(1366/2-100,768/2+100,200,50);
		g.drawImage(graj, 1366/2-100, 768/2);
		g.drawImage(wyjscie, 1366/2-100, 768/2+100);
		
		//g.drawImage(sword, Mouse.getX(), 767-Mouse.getY());
		g.drawString(mouse, 120, 10);
	}
	
	public void update(GameContainer gc, StateBasedGame sbg, int delta)throws SlickException{
		int xpos = Mouse.getX();
		int ypos = 767-Mouse.getY();
		mouse = "Mouse position x: "+ xpos + " y: "+ypos;
		Input input = gc.getInput();
		if(input.isKeyDown(Input.KEY_ESCAPE)){ System.exit(0); }
		if((xpos>(1366/2-100)&&xpos<(1366/2-100+200))  &&  ((ypos>(768/2))&&ypos<(768/2+50)))
		{
			if(input.isMouseButtonDown(0))
			{
				sbg.enterState(1);
			}
		}
		if((xpos>(1366/2-100) && xpos<(1366/2-100+200) )  &&  (ypos>(768/2+100) && ypos<(768/2+100+50) ))
		{
			if(input.isMouseButtonDown(0))
			{
				System.exit(0);
			}
		}
	}
	
	public int getID(){
		return 0;
	}
	
}
