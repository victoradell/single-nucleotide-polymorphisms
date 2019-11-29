import pandas as pd


snp = pd.read_csv('../data/sampled_data.csv')
alleles1, alleles2 = list(snp.Allele1), list(snp.Allele2)
alleles = alleles1 + alleles2


print('Computing most frequent allele for each locus...')
mostFreqs = list()
for i in range(len(alleles[0])):
	if (i%5000==0):
		print(f"Computed first {i} positions")
	locusVals = [allele[i] for allele in alleles]
	mostFreq = [max(set(locusVals), key=locusVals.count)]
	mostFreqs.append(mostFreq)


def encode_row(row, mostFreqs):
    encoded = list()
    for i in range(len(row.Allele1)):
        if row.Allele1[i] != row.Allele2[i]:
            encoded.append(1)
        elif row.Allele1[i] == mostFreqs[i]:
            encoded.append(0)
        else:
            encoded.append(2)
    return encoded

print('Encoding each allele combination (AA->0, AB->1, BB->2')
combinated = snp.apply(lambda row: encode_row(row, mostFreqs), axis=1)
expanded = combinated.apply(pd.Series)
expanded = expanded.rename(columns = lambda x : 'r' + str(x))
snp = snp.join(expanded)
snp.to_csv('../data/Processed_data.csv')
print('Saved into Processed_data.csv')
print(snp.head())