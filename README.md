



This is a game I'm working on creating as a personal project.  I'm using SDL2
for graphics, but everything else is my own C++ code.  At this point, I'm still
building the engine.  I haven't yet bothered naming anything related to it,
hence, the reason why I'm just calling it RPG for now.

I am also using this project to learn Visual Studio.

==RECRUITMENT==================================================================

I'm trying to keep the number of people who work on this to an absolute
minimum, but my artistic ability is unfortunately lacking for anything beyond
some very basic terrain tiles.

Therefore, I'm looking for one person to make me some animated sprite sheets.
Be warned, although I'd love to; as things are for me right now I can't really
afford to pay anyone and I can't promise I will be able to in the future.  So,
for now, it would be completely voluntary.  However, if someone with some
artistic skill needs some programming work done, I'd willing to do that as a
trade.


Eventually, I may also need someone who can make some sound effects, but I
should be able to compose music on my own, but I'm willing to accept other's
work.


Since I'm the only person working on this project right now, please just submit
an issue if you're interested.


For now I'll probably just find someone on [fivver](https://www.fiverr.com)
when I'm ready.


==DEVELOPMENT LOG==============================================================


(03/02/2019) Slowly getting back into working on this after moving overseas and
starting a new job.  The necessity of having some sort of scripting built into
this engine is starting to loom.  Although creating and incorporating my own
scripting language sounds like a fun challenge, I've never really looked into
using another pre-existing scripting language in my own programs, so this in
itself may be a worthwile pursuit.


(26/03/2018) Stepping away from the game for a bit to work on a map editor to
work with it.  That code is largely copied from this code.  The repo for that
is <[https://github.com/tcarrel/RPG_map_editor](https://github.com/tcarrel/RPG_map_editor)>.


(21/03/2018) I'm not very good a making character sprites...  For now, I'm
borrowing part of a sprite sheet from RPG Maker VXace.  I'll replace this when
I'm essentially closer to being done with the software portion of the game's
development.


(20/03/2018) After beginning work on the map/tiling engine, I realize it would
be better to at least create some part of the actor class(es).

I decided I needed some graphical assets.  A sprite sheet for the main
character, in particular.  So I'm mostly working on drawing right now... which
I'm not very good at.  It'll probably be a while...


(16/03/2018) Changing the state machine implimentation, done.  Also added the
"Line Ending Unifier" plug-in to Visual Studio, so an additional file was
added by it.


(14/03/2018) Although I should have realized it before I even began working on
this project, I recently realized that the way I was handling the state machine
that the game is running inside of was overly complicated when I could have
just used a stack instead.  As a result, I'm having to change quite a bit that
I've already written to utilize the normal program stack frame to manage a
large part the state machine functionality for me...  Live and Learn.  I'm
going to hold of on pushing more updates until I've got these changes working,
which may be a while.