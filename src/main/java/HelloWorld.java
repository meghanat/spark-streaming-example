class HelloWorld
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
// public static void main(String[] args)
// {
// HelloWorld h = new HelloWorld();
// h.sayHi("JNI");
// h.printPID();
// h.printSchedType();
// h.setSchedType();
// h.printSchedType();
// }
}