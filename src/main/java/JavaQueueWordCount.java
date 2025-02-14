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

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Arrays;
import java.io.FileReader;  
import java.io.BufferedReader;
import java.util.regex.Pattern;

import scala.Tuple2;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.streaming.Duration;
import org.apache.spark.streaming.api.java.JavaDStream;
import org.apache.spark.streaming.api.java.JavaPairDStream;
import org.apache.spark.streaming.api.java.JavaStreamingContext;

public final class JavaQueueWordCount {
  private static final Pattern SPACE = Pattern.compile(" ");
  
  private JavaQueueWordCount() {
  }

  public static void main(String[] args) throws Exception {

    // StreamingExamples.setStreamingLogLevels();
    SparkConf sparkConf = new SparkConf().setAppName("JavaQueueWordCount");

    // Create the context
    JavaStreamingContext ssc = new JavaStreamingContext(sparkConf, new Duration(1000));


    // Create the queue through which RDDs can be pushed to
    // a QueueInputDStream

    // Create and push some RDDs into the queue
    // List<Integer> list = new ArrayList<>();
    // for (int i = 0; i < 1000; i++) {
    //   list.add(i);
    // }
    List<String> list = new ArrayList<>();
    try (BufferedReader br = new BufferedReader(new FileReader("/home/hduser/data/alice"))) {
      String line;
      while ((line = br.readLine()) != null) {
        list.add(line);
      }
    }

    Queue<JavaRDD<String>> rddQueue = new LinkedList<>();
    for (int i = 0; i < 30; i++) {
      rddQueue.add(ssc.sparkContext().parallelize(list));
    }

    // Create the QueueInputDStream and use it do some processing
    JavaDStream<String> inputStream = ssc.queueStream(rddQueue);
    JavaDStream<String> words = inputStream.flatMap(x -> Arrays.asList(SPACE.split(x)).iterator());
    JavaPairDStream<String, Integer> wordCounts = words.mapToPair(s -> new Tuple2<>(s, 1))
        .reduceByKey((i1, i2) -> i1 + i2);

    wordCounts.print();
    ssc.start();
    ssc.awaitTermination();
  }
}
