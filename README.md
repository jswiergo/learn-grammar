Learn Grammar
=============

## Introduction ##

The Learn Grammar is an experiment of unsupervised language grammar learning based on previous works
within OpenCog project by Linas Vepstas and GSoC 2015 student Rohid Shinde.

You can find theoretical introduction to the problem solution in Deniz Yureth PhD thesis:
- http://www2.denizyuret.com/pub/yuretphd.pdf

Description of the project steps and its current status of implementation in OpenCog you can find here:
- https://arxiv.org/abs/1401.3372 (Learning Language from a Large (Unnanoted Corpus))
- http://wiki.opencog.org/w/Language_learning
- https://github.com/opencog/opencog/blob/master/opencog/nlp/learn/README

More practical details of previous experiment by Rohid Shinde on OpenCog mailing list Q&A:
- https://groups.google.com/forum/#!topic/opencog/8HWcT2kKxX0[1-25] (Student looking to contribute toward OpenCog)  (196 posts)
- https://groups.google.com/forum/#!topic/opencog/46nNwuh3RVc       (Unsupervised Language Learning (Summary)) 
- https://groups.google.com/forum/#!topic/opencog/Qs4ZZP0Gg0k       (Regarding GSoC 2015 projects)
- https://groups.google.com/forum/#!topic/opencog/lcfiwe_ao08       (Re: GSoC coding) 
- https://groups.google.com/forum/#!topic/opencog/gmrSdo9OzC8       (automated discovery of grammatical classes)
- https://groups.google.com/forum/#!topic/opencog/2Ech9y_B8ZY       (Summary of grammar discovery)
- https://groups.google.com/forum/#!topic/opencog/q0Uac8mJUgs       (Cosine Distance of words)

## Dependencies ##

**Link Grammar Parser**

- https://github.com/opencog/link-grammar

Build and installation of Link Grammar library is required.

**RelEx Semantic Relation Extractor**

- https://github.com/opencog/relex

Build is not required. We are using only a few utility scripts for parsing Wikipedia articles and spliting sentences.
