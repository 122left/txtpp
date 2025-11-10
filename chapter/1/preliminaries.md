# Preliminaries

_To remember:_ is that there's not much programmatic in Introductory TA.

## Structured vs Unstructured Data

**Structured**:

- Ordered numerical attributes: meaningful < or > comparisons
- Categorical coding to represent attributes: sequential order does not matter
- Spreadsheet format: columns are attributes, rows are instances
- Quantitative
- Readily data mine-able
- Not necessarily sparse
- Deals with all kinds of numerical values
- Missing data *must* be handled

**Unstructured (Text)**:

- Lesser meaningful comparisons
- Sequential order matters here
- Document format, such as via XML, with data that is not inherently numerical
- Qualitative
- Needs to be transformed into structured data first
- Spreadsheet conversions are sparse
- Focus on positive values (word presences)
- Missing data is a nonissue

## Types of problems solveable

1. **Classification and Prediction**

- Predict correct answers for new examples based on past data.
- Use samples of past experiences with known outcomes to train models.
- Binary categorisation: a document may either belong to a specified class or not
- E.g. text categorisation, information retrieval: find relevant documents for a query
- Apps: email management, info organisation/indexes, news article with metrics to predict prices

2. **Clustering and Organising Documents**

- Assumes no prior knowledge of topics or clusters
- Organises documents into clusters or relatability based on similarity
- Effectively creates categories, at least one new column to the spreadsheet
- Apps: group related customer support queries, market analysis, exploration
- Limits: less precise than categorisation, multiple solutions exist

3. **Information Extraction**:

- Transforms unstructured data into structured counterparts
- Automatically fills in values of a spreadsheet/DB table from documents
- Climbs above basic text mining to uncover concepts and attributes
- Apps: extracting financial metrics, populating DBs with info from the web, reports and e-mails
- Challenges: text attributes require sophisiticated techniques to extract, not word-based
- Process: collect documents -> standardise