# NTL
NTL stands for Note-Taking Language and is a simple markup language written with speed and readability in mind.

Please note this project is no longer maintained, and will not compile due to major changes to its dependencies (PoDoFo).

## The Idea
The idea begin NTL is that no one should have to worry about formatting their notes while they're writing them, all focus should be on the content itself.
The way this is adressed is by using single-character commands for elements such as the document title, list names, section names etc. 
Once the .ntl document has been written, presumably once the lecture or meeting is over, the user can then run this program (yet to be formally named) which uses the information held in the document to produce a nicely formatted pdf document.
This means that the user does not have to bother with manually formatting anything, during or after writing their notes.

## Building the tool
To build the program in this repo, all you must do is check the program's dependancies, and type
```
make all
```
into your terminal.  
### Dependancies
[PoDoFo](http://podofo.sourceforge.net/)
[pdfLaTeX](https://tug.org/texlive/)

I personally use the texlive package for building my LaTeX documents but any package which includes the "pdflatex" tool will work with this program, for example [MikTeX](https://miktex.org/) is another option.

## Alternative Parser
Stephan Kreutzer has developed his own parser for NTL, which supports output to raw XML, HTML and PDF.  This project can be found [here](https://github.com/publishing-systems/ntl).

## Syntax
More features may be added to the language, but the commands that have currently been established are shown below.

### Title
```
#t Dynamics
```
The above would set the documents title to "Dynamics".

### Lists
```
#l List title
 list item
 another list item
```
The above creates a list named "List title", and contains the items, "list item" and "another list item".
If your list does not require a title, list items can still be created by leading the line with a space, this will be useful for bullet pointing important pieces of information.

### Regular text
```
This is a regular sentence.  All regular text will be turned into a paragraph until the characters "//" are detected, in which case a new paragraph is started.
```
### Sectioning
```
#s Rotational Dynamics
```
The above will create a section named "Rotational Dynamics".  In general most notes are short and concise, so I have no plans on generating a table of contents for each document at the moment, but it may be implemented at a later stage.

### Highlighting
```
We define the :: center of mass :: of a system of particles (such as a person) in order to predict the possible motion of the system.
```
The above will highlight the words, "center of mass", and in any case will highlight words contained within double colons.

### Lines/breaks
```
#b
```
The above draws a horizontal line across the page in order to separate information.  The command used is "#b" for "break" since "#l" is already in use.

### Equations
```
#e f = f_0\left( 1 = \frac{v}{c} \right)
```
Equations are generated using pdflatex, and so at the moment, after the "#e" has been typed, anything else on the line should be written with LaTeX's equation/math syntax.  I do understand, however, that LaTeX can be a little verbose, so at a later stage I will try to abstract it a little so that it's faster to type, but for now it is more important that equations actually work.

## Additional information
The development of this language and parser/pdf-generator can be followed live on my [twitch.tv channel](https://www.twitch.tv/that__guy2)
