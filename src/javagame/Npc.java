package javagame;

public abstract class Npc {

	public int oldx;
	public int oldy;
	public int x;
	public int y;
	public int health;
	public int attackspeed;
	public int movementspeed;
	public int attackdamage;
	public abstract void movement();
	
}
