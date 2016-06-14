package javagame;


public class Player extends Npc{

	Player(){
		x=200;
		y=768/2;
		movementspeed = 4;
		health = 100;
		attackdamage=5;
		attackspeed = 15;
		experience = 0;
		licznik = 0;
		level = 1;
		wynik = 0;
	}
	
	
	public void movement() {
		if(x<0)
		{
			x=oldx;
		}
		if(x>1366-40)
		{
			x=oldx;
		}
		if(y>768-40)
		{
			y=oldy;
		}
		if(y<0)
		{
			y=oldy;
		}
		oldx=x;
		oldy=y;
	}
	
	public void experiencecheck()
	{
		if(10+level*10 <= experience)
        {
            experience=0;
            levelup();
        }
	}
	
	public void experienceadd(int a)
	{
		experience = experience + a;
	}

	private void levelup(){
		if(level>=20)
        {
            //nic nie rob
        }
        else
        {
            level++;
            health=100;
            //attackdamage++;
            if(level%5==0)
            {
                movementspeed++;
            }
            if(level%2==1)
            {
                attackspeed--;
            }
            //health = 100+getlevel()*5;
            experience=0;
            wynik=wynik+10;
        }
	}
	
	public int getLevel()
	{
		return level;
	}
	
	public int getWynik()
	{
		return wynik;
	}
	
	public int licznik;
	private int experience;
	private int level;
	public int wynik;
}
