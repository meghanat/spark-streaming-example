/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import scala.Tuple2;

import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.function.*;
import org.apache.spark.sql.SparkSession;
import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaSparkContext;

import org.apache.log4j.Logger;
import org.apache.log4j.Level;

import java.util.Iterator;
import java.util.Arrays;
import java.util.List;
import java.util.regex.Pattern;
import java.util.concurrent.TimeUnit;

import java.util.concurrent.atomic.*;

import java.lang.Thread;

class Scheduler extends Thread{
   private final AtomicBoolean running = new AtomicBoolean(false);

  public  void run()
    {
          // System.out.println("MyThread running");
          
          Deadline h = new Deadline();
          running.set(true);
          
          while(running.get()){
            try 
            {
                h.scheduleAll();
                Thread.sleep(500);
            } 
            catch(InterruptedException e)
            {
                 // this part is executed when an exception (in this example InterruptedException) occurs
            }
          }
          
    }
     public void stopThread() {
        running.set(false);
    }

}

public final class JavaWordCount extends Thread {


  private static final Pattern SPACE = Pattern.compile(" ");

  

  public static void main(String[] args) throws Exception {


    int total=0;
    if (args.length < 1) {
      System.err.println("Usage: JavaWordCount <file>");
      System.exit(1);
    }
    Scheduler scheduler=new Scheduler();
    scheduler.start();
    Logger.getLogger("org").setLevel(Level.ERROR);
    SparkConf sparkConf = new SparkConf().setAppName("JavaWordCount");

    
    JavaSparkContext spark= new JavaSparkContext(sparkConf);
    long startTime = System.nanoTime();
    JavaRDD<String> lines = spark.textFile(args[0]);
    
    
    JavaRDD<String> tweet = lines.map(new Function<String,String>(){

      private static final long serialVersionUID = 1L;
     
      
      public String call(String line){
          
          String []values=line.split(",",6);
          return values[5];
      }
    });

    JavaRDD<String> words = tweet.flatMap(
      new FlatMapFunction<String, String>() {

       public Iterator call(String x) {
          return Arrays.asList(x.split(" ")).iterator();
        }});


    JavaPairRDD<String, Integer> ones = words.mapToPair(
      new PairFunction<String, String, Integer>() {
      
        @Override
        public Tuple2<String,Integer> call(String w) {
          
          return new Tuple2(w, 1);
        }
    });


    JavaPairRDD<String, Integer> wordCount = ones.reduceByKey(new Function2 <Integer,Integer,Integer>(){
     
      
      @Override
      public Integer call(Integer i1, Integer i2){
        return i1+i2;
      }

    });
    
    List<Tuple2<String, Integer>> output = wordCount.collect();
    // for (Tuple2<?,?> tuple : output) {
    //   System.out.println(tuple._1() + ": " + tuple._2());
    // }
    spark.stop();
    scheduler.stopThread();
    long endTime = System.nanoTime();
    long timeElapsed = endTime - startTime;
    System.out.println("Execution time in nanoseconds  : " + timeElapsed);

    System.out.println("Execution time in milliseconds : " + 
                timeElapsed / 1000000);
  }
}
