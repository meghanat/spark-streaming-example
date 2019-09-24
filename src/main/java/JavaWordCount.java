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
import org.apache.spark.api.java.function.PairFunction;
import org.apache.spark.api.java.function.Function2;
import org.apache.spark.sql.SparkSession;
import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaSparkContext;

import org.apache.log4j.Logger;
import org.apache.log4j.Level;


import java.util.Arrays;
import java.util.List;
import java.util.regex.Pattern;

import java.lang.Thread;

public final class JavaWordCount {
  private static final Pattern SPACE = Pattern.compile(" ");

  public static void main(String[] args) throws Exception {

    int total=0;
    if (args.length < 1) {
      System.err.println("Usage: JavaWordCount <file>");
      System.exit(1);
    }

    Logger.getLogger("org").setLevel(Level.ERROR);
    SparkConf sparkConf = new SparkConf().setAppName("JavaWordCount");


    // System.out.println("Hello Worlds");
    HelloWorld h = new HelloWorld();
    // h.sayHi("JNI");
    h.printPID();
    // h.printSchedType();
    h.setSchedType();
    // h.printSchedType();
    Thread.sleep(10000);   
    JavaSparkContext spark= new JavaSparkContext(sparkConf);

   
    JavaRDD<String> lines = spark.textFile(args[0]);


    JavaPairRDD<String,Double> yearlyRain = lines.mapToPair(new PairFunction<String,String,Double>(){

      private static final long serialVersionUID = 1L;
      int total=0;
      public Tuple2<String,Double> call(String line){
        String []values=line.split(",");
        try{
          // int pid=h.getPID();

           // h.setSchedType();
           total++;
          // System.out.println(Integer.toString(pid));

          return new Tuple2<String,Double>(values[0],new Double(values[14]));  
        }
        catch(NumberFormatException e){

          return new Tuple2<String,Double>(values[0],0.0);
        }
        
      }
    });
    // JavaPairRDD<String, Double> maxRainfall = yearlyRain.reduceByKey((i1, i2) -> Math.max(i1, i2));

    JavaPairRDD<String, Double> maxRainfall = yearlyRain.reduceByKey(new Function2 <Double,Double,Double>(){
      int total=0;
      @Override
      public Double call(Double i1, Double i2){
        total++;
        // h.setSchedType();
        // System.out.println(Integer.toString(total));
        // h.printPID();
        return Math.max(i1,i2);
      }

    });

    List<Tuple2<String, Double>> output = maxRainfall.collect();
    for (Tuple2<?,?> tuple : output) {
      System.out.println(tuple._1() + ": " + tuple._2());
    }
    // spark.stop();
  }
}
