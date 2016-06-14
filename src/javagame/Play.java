package javagame;


import java.text.SimpleDateFormat;
import java.util.Date;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
//import java.io.PrintWriter;
import java.util.Random;

import org.newdawn.slick.*;
import org.newdawn.slick.state.*;

public class Play extends BasicGameState{
	
	File plik = new File("wyniki.txt");
	
	Random random = new Random();
	
	Image bg;
	Image statek;
	Image ppocisk;
	Image epocisk;
	Image enemya;
	Image enemyb;
	Image enemyc;
	Image end;
	Image boom;
	Player player;
	Pammo pammo[] = new Pammo[20];
	Eammo eammo[] = new Eammo[20];
	Enemy enemy[] = new Enemy[20];
	
	public Play(int state){
		zapisz=true;
		for(int i=0;i<20;i++)
		{
			int los = random.nextInt(3);
			switch(los)
			{
			case 0: enemy[i] = new Light();
			break;
			case 1: enemy[i] = new Medium();
			break;
			case 2: enemy[i] = new Heavy();
			break;
			}
		}
		timer = 0;
	}
	
	public void init(GameContainer gc, StateBasedGame sbg)throws SlickException{
		bg = new Image("res/bg.bmp");
		statek = new Image("res/player.png");
		ppocisk = new Image("res/pocisk.bmp");
		epocisk = new Image("res/epocisk.bmp");
		enemya = new Image("res/enemya.png");
		enemyb = new Image("res/enemyb.png");
		enemyc = new Image("res/enemyc.png");
		end = new Image("res/end.png");
		boom = new Image("res/boom.png");
		player = new Player();
		
		for(int i=0;i<20;i++)
		{
			eammo[i] = new Eammo();
			pammo[i] = new Pammo();
		}
		
		
	}
	
	public void render(GameContainer gc, StateBasedGame sbg, Graphics g)throws SlickException{
		g.drawImage(bg , 0, 0);
		for(int i=0;i<player.getLevel();i++)
		{
			if(enemy[i].ID==0){g.drawImage(enemya , enemy[i].x, enemy[i].y);}
			if(enemy[i].ID==1){g.drawImage(enemyb , enemy[i].x, enemy[i].y);}
			if(enemy[i].ID==2){g.drawImage(enemyc , enemy[i].x, enemy[i].y);}
		}
		for(int i=0;i<20;i++)
		{
			g.drawImage(ppocisk, pammo[i].x, pammo[i].y );
			g.drawImage(epocisk, eammo[i].x, eammo[i].y );
		}
		g.drawImage(statek, player.x, player.y );
		g.drawString("Wynik: "+ Integer.toString(player.getWynik()) , 10, 30);
		g.drawString("Poziom: "+ Integer.toString(player.getLevel()) , 10, 50);
		g.drawString("Zycie: "+ Integer.toString(player.health) , 10, 70);
		if(player.health<=0)
		{
			g.drawImage(end, 1366/2-250, 768/2-100 );
		}
		
		for(int i=0;i<20;i++)
		{
			for(int q=0;q<player.getLevel();q++)
			{
				if(Distance(enemy[q].x,pammo[i].x,enemy[q].y,pammo[i].y)<20)
				{
					g.drawImage(boom, enemy[q].x, enemy[q].y );
					//lag(10);
				}
				if(Distance(player.x,eammo[i].x,player.y,eammo[i].y)<20)
				{
					g.drawImage(boom, player.x, player.y );
					//lag(10);
				}
			}
		}
		
		
		delay(); //zmniejszanie fps
	}
	
	public void update(GameContainer gc, StateBasedGame sbg, int delta)throws SlickException{
		int los;
		Input input = gc.getInput();
		if(player.health>0)
		{
			if(input.isKeyDown(Input.KEY_DOWN)){ player.y=player.y+player.movementspeed; }
			if(input.isKeyDown(Input.KEY_UP)){ player.y=player.y-player.movementspeed; }
			if(input.isKeyDown(Input.KEY_LEFT)){ player.x=player.x-player.movementspeed; }
			if(input.isKeyDown(Input.KEY_RIGHT)){ player.x=player.x+player.movementspeed; }
			if(input.isKeyDown(Input.KEY_SPACE)){ 
				
				if((timer-cooldown)>player.attackspeed)
				{
					if(player.licznik>=20)
	                {
	                    player.licznik=0;
	                }
	                pammo[player.licznik].x=player.x+10;
	                pammo[player.licznik].y=player.y+10;
	                cooldown=timer;
	                player.licznik++;
				}
				
				
				//strzaly
			}
		}
		else
		{
			try {
				zapis();
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}
		
		if(input.isKeyDown(Input.KEY_ESCAPE)){ try {zapis();} catch (FileNotFoundException e) {e.printStackTrace();} if(player.health<=0){  lag(500); System.exit(0); } else { lag(400); sbg.enterState(0);}}
		if(input.isKeyDown(Input.KEY_0)){ player.experienceadd(10); player.health--; }
		
		
		
		for(int i=0;i<20;i++)
		{
			pammo[i].ruch();
			eammo[i].ruch();
			
			for(int q=0;q<player.getLevel();q++)
            {
                if(Distance(enemy[q].x,pammo[i].x,enemy[q].y+5,pammo[i].y)<20)
                {
                    enemy[q].health=enemy[q].health-player.attackdamage;
                    pammo[i].x=2000;
                }
                if(enemy[q].health<=0)
                {
                	enemy[q].ReHealth();
                    enemy[q].x=1300;
                    enemy[q].oldx=1300;
                    player.experienceadd(10);
                    player.wynik++;
                }
            }
			
			if(Distance(player.x,eammo[i].x,player.y+10,eammo[i].y)<20)
			{
				player.health=player.health-enemy[i].attackdamage;
				eammo[i].x=-100;
			}
			if(Distance(player.x,enemy[i].x,player.y,enemy[i].y)<20)
			{
				player.health=0;
			}
			
		}
		
		for(int i=0;i<player.getLevel();i++)
		{
			if(eammo[i].x<=0)
            {
                los = random.nextInt(100) + 0;
                if(los==5)
                {
                    eammo[i].x=enemy[i].x;
                    eammo[i].y=enemy[i].y;
                }

            }
			
			enemy[i].movement();
		}
		player.movement();
		player.experiencecheck();
	}
	
	public void delay(){
		try {
			timer++;
		    Thread.sleep(1000/30);
		} catch(InterruptedException ex) {
		    Thread.currentThread().interrupt();
		}
	}
	
	public void lag(int a){
		try {
		    Thread.sleep(a);
		} catch(InterruptedException ex) {
		    Thread.currentThread().interrupt();
		}
	}
	
	public int Distance(int x1, int x2, int y1, int y2){
		return (int) Math.sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	}
	
	public int getID(){
		return 1;
	}
	
	public void zapis() throws FileNotFoundException{
		if(zapisz==true)
		{
			SimpleDateFormat simpleDateHere = new SimpleDateFormat("yyyy-MM-dd kk:mm:ss (Z)");
	        //System.out.println( simpleDateHere.format(new Date()) );
			
			
			FileWriter out = null;
			try {
				out = new FileWriter("wyniki.txt", true);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			BufferedWriter zapis = new BufferedWriter(out);
			try {
				zapis.write("Grano przez: "+timer/30+" sekund, zdobyto "+player.wynik+ " punktow "+simpleDateHere.format(new Date())+System.getProperty("line.separator"));
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			try {
				zapis.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			zapisz=false;
		}
	}
	
	private boolean zapisz;
	private int timer;
	private int cooldown;
}
