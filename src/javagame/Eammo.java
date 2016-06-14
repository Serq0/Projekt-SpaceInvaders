package javagame;

public class Eammo extends Pociski{

	Eammo()
	{
		x=-500;
		y=2000;
	}
	
	void ruch() {
		if(x>-10)
		{
			x=x-10;
		}
	}

}
