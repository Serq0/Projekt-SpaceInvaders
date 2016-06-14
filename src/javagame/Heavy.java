package javagame;

public class Heavy extends Enemy{

	Heavy(){
		ID = 2;
		movementspeed = 1;
        health = 55;
        attackdamage = 12;
	}
	

	@Override
	public void ReHealth() {
		health = 55;
		
	}
	
}
