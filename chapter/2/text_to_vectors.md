# Text to Vectors

_Here_ is where the hands-on stuff truly begins.

The pipeline goes like this:

Tokenisation -> Lemmatisation -> Vector generation -> Feature selection

## Tokenisation

Types: word, subword, character, sentence
Special characters: always treated as delimiters, except . , : - ' (context-dependant)

[Tokenisation! Refer to the tokenisation_example.cpp file]

Now that we're done with that,

## Lemmatisation

Process of reducing words to a base form found in dictionaries, called 'lemma'.
It primarily uses morphological analysis and PoS context.
It is more linguistically-based and context-aware, and produces valid words.

Found in: search engines, chatbots, sentiment analysis, information retrieval, classification, clustering.

### Stemming

Stemming reduces a word to root forms by heuristic removal of suffixes and prefixes.
While different from lemmatisation and generally faster, it does not guarantee valid words.

Types: inflectional (affix-focused) and to-root.

