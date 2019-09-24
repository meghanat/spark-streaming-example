import java.io.Serializable;
import java.lang.Thread;
class HelloWorld extends Thread implements Serializable 
{
		public native void sayHi(String name);
		static
		{
			System.loadLibrary("hello");
		}

		public native void printPID();
		static
		{	
			System.loadLibrary("hello");
		}
		public native int getPID();
		static
		{	
			System.loadLibrary("hello");
		}
		public native void printSchedType();
		static
		{
			System.loadLibrary("hello");
		}
		public native void setSchedType();
		static
		{
			System.loadLibrary("hello");
		}
		public void run()
		{
       		System.out.println("MyThread running");
       		this.printSchedType();
       		this.setSchedType();
       		for(int j=0;j<100000000;)
			{
				int num = 12/1822*43884348/579849;
				num = 12/1822*43863348/579849;
				num = 12/1822*43384348/579849;
			}
       		this.printSchedType();

    	}

public static void main(String[] args)
{
HelloWorld h = new HelloWorld();
HelloWorld h1 = new HelloWorld();
h.sayHi("JNI");
h.printPID();
System.out.println("Main Thread");
h.printSchedType();

// h.setSchedType();
h.printSchedType();
h.start();
h1.start();
}
}