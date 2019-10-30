1. After editing Deadline.java:
javac Deadline.java -h .
2. Compile c library to create library:
gcc -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -shared -o libdeadline.so deadline.c
3.From project's main directory:
mvn clean package 
4. Then, to run spark program with shared library :
 sudo <path-to-spark>/bin/spark-submit --master local[*] --driver-memory 12g  --class "JavaWordCount" target/spark-real-time-0.0.1.jar ../data/training.1600000.processed.noemoticon.csv 
