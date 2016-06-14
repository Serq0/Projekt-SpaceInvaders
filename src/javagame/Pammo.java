package javagame;

public class Pammo extends Pociski{

	Pammo()
	{
		x=2000;
		y=2000;
	}
	
	void ruch() {
		if(x<1400)
		{
			x=x+10;
		}
	}

}
