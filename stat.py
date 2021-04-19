import pandas as pd
import sys


sizes = [64, 128, 256, 512, 1024, 2048]
dfs = []
for index, size in enumerate(sizes):
  df=pd.read_csv("benchmark/"+sys.argv[1]+"/"+str(size)+".csv")
  # print(sys.argv[1], df.mean()[0], df.mean()[1])
  dfs.append(df.mean())

# print(sys.argv[1], dfs[1])
print(
  # sys.argv[1],
  # 'latency',
  dfs[0][0],',',
  dfs[1][0],',',
  dfs[2][0],',',
  dfs[3][0],',',
  dfs[4][0],',',
  dfs[5][0],',',
  # dfs[1]['latency'].mean(),
  # dfs[2]['latency'].mean(),
  # dfs[3]['latency'].mean(),
  # dfs[4]['latency'].mean(),
  # dfs[5]['latency'].mean(),
  # 'throughput',
  dfs[0][1],',',
  dfs[1][1],',',
  dfs[2][1],',',
  dfs[3][1],',',
  dfs[4][1],',',
  dfs[5][1],
  # dfs[1][['throughput']].mean(),
  # dfs[2]['throughput'].mean(),
  # dfs[3]['throughput'].mean(),
  # dfs[4]['throughput'].mean(),
  # dfs[5][['throughput']].mean()
)