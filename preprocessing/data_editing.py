import os
import pandas as pd
import time
import glob


EXTENSION = 'csv'

os.chdir('../data/raw_data')
allFilenames = [i for i in glob.glob('*.{}'.format(EXTENSION))]
for fileName in allFilenames:
	print(f"Reading {fileName}...", end=' ')
	pop = fileName.split('_')[0][:-1]
	popDF = pd.read_csv('raw_data/'+fileName)
	popDF.drop(columns=['ParentM', 'ParentF', 'EthA', 'EthE', 'EthK', 'EthP'], inplace=True)
	popDF['Population'] = pop
	popDF.to_csv('../data/processed_data/'+fileName[:-4]+'_processed.csv', index=False)
	print("finished processing file.")


os.chdir('../processed_data')
allFilenames = [i for i in glob.glob('*.{}'.format(EXTENSION))]
combined_csv = pd.concat([pd.read_csv(f).sample(125) for f in allFilenames])
combined_csv.to_csv('sampled_data.csv', index=False)