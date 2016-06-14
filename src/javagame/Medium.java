package javagame;

public class Medium extends Enemy{
	
	Medium(){
		ID = 1;
		movementspeed = 2;
        health = 35;
        attackdamage = 8;
	}


	@Override
	public void ReHealth() {
		health = 35;
		
	}
	
}
