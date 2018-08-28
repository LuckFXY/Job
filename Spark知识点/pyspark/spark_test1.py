

from pyspark import SparkContext
sc = SparkContext("local[*]", "test")

logFile = r"file:///usr/local/spark/README.md"
logData = sc.textFile(logFile, 2).cache()
numAs = logData.filter(lambda line: 'a' in line).count()
numBs = logData.filter(lambda line: 'b' in line).count()
print('Lines with a: %s, Lines with b: %s' % (numAs, numBs))
'''
from pyspark import SparkContext
from pyspark.streaming import StreamingContext

#sc = SparkContext("spark://110.9.17.187:8070", "NetworkWordCount")
from pyspark import SparkConf, SparkContext
conf = SparkConf().setMaster("local").setAppName("MY First App")
sc = SparkContext(conf = conf)

data = [1, 2, 3, 4, 5]
distData = sc.parallelize(data)
distData.reduce(lambda a, b: a + b)
'''
