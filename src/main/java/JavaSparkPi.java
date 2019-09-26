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
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;
import java.util.concurrent.TimeUnit;

import java.lang.Thread;

public final class JavaSparkPi {
  private static final Pattern SPACE = Pattern.compile(" ");

  public static void main(String[] args) throws Exception {

    HelloWorld h = new HelloWorld();
    
    h.setSchedType();
    

    int total=0;
    // if (args.length < 1) {
    //   System.err.println("Usage: JavaWordCount <file>");
    //   System.exit(1);
    // }

    Logger.getLogger("org").setLevel(Level.ERROR);
    h.setSchedType();
    SparkConf sparkConf = new SparkConf().setAppName("JavaSparkPi");
    h.setSchedType();

    JavaSparkContext spark= new JavaSparkContext(sparkConf);
    h.setSchedType();
    long startTime = System.nanoTime();
      
     int slices = (args.length == 1) ? Integer.parseInt(args[0]) : 2;
    int n = 10000000 * slices;
    List<Integer> l = new ArrayList<>(n);
    for (int i = 0; i < n; i++) {
      l.add(i);
    }

    JavaRDD<Integer> dataSet = spark.parallelize(l, slices);



    JavaRDD <Integer> loop= dataSet.map(new Function<Integer,Integer>(){

       boolean set=false;
       {
        h.setSchedType();
       }

      public Integer call(Integer num){
        if(!set){
            set=true;
            h.setSchedType();
          }


      double x = Math.random() * 2 - 1;
      double y = Math.random() * 2 - 1;
      return (x * x + y * y <= 1) ? 1 : 0;

    }
  });

    int count=loop.reduce(new Function2<Integer,Integer,Integer>(){
        {
          h.setSchedType();
        }
        boolean set=false;
      
       @Override
      public Integer call(Integer i1, Integer i2){
        if(!set){
            set=true;
            h.setSchedType();
          }
        return i1+i2;
      }


    });

    spark.stop();

    System.out.println("Pi is roughly " + 4.0 * count / n);


    long endTime = System.nanoTime();
    long timeElapsed = endTime - startTime;
    System.out.println("Execution time in nanoseconds  : " + timeElapsed);

    System.out.println("Execution time in milliseconds : " + 
                timeElapsed / 1000000);
  }

}
