
public class HelloWorld{
	private static int score = 84;
	public static class SInner{
		int score = 91;
		public void show(){
			System.out.println("Outsite score : " + HelloWorld.score);
			System.out.println("Inside score : " + score);
		}
		
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		SInner si = new SInner();
		si.show();
	}

}
