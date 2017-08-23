# NTL
NTL stands for Note-Taking Language and is a simple markup language written with speed and readability in mind.

## The Idea
The idea begin NTL is that no one should have to worry about formatting their notes while they're writing them, all focus should be on the content itself.
The way this is adressed is by using single-character commands for elements such as the document title, list names, section names etc. 
Once the .ntl document has been written, presumably once the lecture or meeting is over, the user can then run this program (yet to be formally named) which uses the information held in the document to produce a nicely formatted pdf document.
This means that the user does not have to bother with manually formatting anything, during or after writing their notes.

## XML Output
If you prefer to have your notes turned into xml files rather than pdf, Stephan Kreutzer has created an alternative ntl parser which produces an xml output instead.  This project can be found [here](https://github.com/publishing-systems/ntml).

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

## Additional information
The development of this language and parser/pdf-generator can be followed live on my [twitch.tv channel](https://www.twitch.tv/that__guy2)
