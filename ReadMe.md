## REPOSITORY STRUCTURE

This project uses kernel methods to classify the ethnic groups given the father's and mother's allele sequences. For specific details of the implementation, refer to <b>report.pdf</b>.

The code for the data preprocessing can be found in the <b>preprocessing</b> directory.

The code for building the kernel matrices from the processed data can be found in the **kernel_matrices** directory.

The code for training and predicting the data can be found in the **kernel_methods** directory.

Some data exploration and visualizations can be found in the jupyer notebooks and R files in the **notebooks** directory.

The **src** and **articles** contain images and articles, correspondingly, used for the creation of the report.

In the **data** directory, you can find the processed data, used for modeling and commented in the report.



## HOW TO

To reproduce the steps to obtain the results explained in the report, the files that should be on **data/raw_data** directory must be downloaded, as its total size is aroung 5GB. The four files are csvs:

* [Afircan American Population Data](https://dataverse.harvard.edu/file.xhtml?persistentId=doi:10.7910/DVN/IDT8HZ/SIISV3&version=3.0)
* [Estonian Population Data](https://dataverse.harvard.edu/file.xhtml?persistentId=doi:10.7910/DVN/IDT8HZ/BGMASX&version=3.0)
* [Korean Population Data](https://dataverse.harvard.edu/file.xhtml?persistentId=doi:10.7910/DVN/IDT8HZ/GEMZGX&version=3.0)
* [Palestinian Population Data](https://dataverse.harvard.edu/file.xhtml?persistentId=doi:10.7910/DVN/IDT8HZ/VMTYYI&version=3.0)

Once downloaded, they must be copied into the directory in order for the data preprocessing scripts in the **preprocessing** folder work properly, and generate the **Processed_data.csv** file in the **data** directory.

