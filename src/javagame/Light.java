package javagame;

public class Light extends Enemy {
	
	Light(){
		ID = 0;
		movementspeed = 3;
        health = 20;
        attackdamage = 5;
	}


	@Override
	public void ReHealth() {
		health = 20;
		
	}
	
}
