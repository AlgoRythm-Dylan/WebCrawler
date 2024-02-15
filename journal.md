# Journal
This is my first big c++ project, and I am learning a lot.
I am keeping a journal here to document what I've learned.
This is an unstructured document where I may reflect on
anything I determine to be of value.

## Organizing Visual Studio projects
Visual Studio groups up C(++) projects into header and 
implementation files. These files, no matter where they
are on the actual file tree, are all shown next to each
other in a list.

This is actually really nice, in my opinion, but can
become a horrendous, unhelpful infinity-scroll for
larger projects.

Visual studio offers the ability to change the tree
to a filesystem representation, but it's just not
the same. It's just not as nice. So what's the best
of both worlds?

Static libraries.

For each logical "module" of your solution - for example,
the HttpClient - create a new project in visual studio
that compiles to a static library. Then, add that
library's folder path to your pain project's "additional
include directories" option, and add the project reference.

Now your solution explorer tree is grouped up by
project and you get to keep the nice .h/.cpp sorting
which is default in VS.

## std::optional
c++ is not like the other girls. A string can't point to
null, because in other languages, objects aren't objects:
they're usually references to objects. Take the following
c# code:

```c#
string something = null;
```

This is perfectly allowed, because something isn't really
a "string", its actually a reference to a string.

The difference is in c++, the following really is a string:

```c++
string something;
```

And thus, it cannot be `nullptr`, because `nullptr` is not
a valid string.

An older approach might be to use a pointer to a string,
so that we can check if it is null or not.

```c++
string *something = nullptr;
```

This is fine, but it does require allocation on the heap and
we need to make sure we clean up that pointer! A better
and more modern approach is to use `std::optional`:

```c++
optional<string> something;
```

We can check if it has a value like such:

```c++
if(something.has_value())
{
    cout << "Something exists!\n";
}
else
{
    cout << "Missing something...?\n";
}
```

## Virtual destructors
This is actually the reason I wanted to make this journal.
This is such a fundamental and important thing to learn,
but I never knew about it until it was already causing
problems in my code.

If you're going to design a class that is meant to be
derived from, **give it a virtual destructor!!**

```c++
class Token
{
public:
    int a;
};

class StringToken : public Token
{
public:
    string value;
}
```

Now, if you have a list of pointers to tokens, such as:
```c++
vector<unique_ptr<Token>> tokens;
```

When that list gets freed, `value` will not! Why? Because
the `Token` is getting destructed, but the `StringToken`
is **NOT**.

So instead, just add an empty virtual destructor in the
Token class, and everything will be groovy.

```c++
class Token
{
public:
    int a;

    virtual ~Token();
};

// ---- Token.cpp ---- //

Token::~Token() {}
```

## Smart Pointers
The modern c++ developer need not ever use raw pointers
when available to him or her is the smart pointer.
There two and a half types of smart pointer, included
in the `<memory>` header:

- unique_ptr
- shared_ptr
- weak_ptr

Smart pointers, critically, free the resource they are
pointing to when they fall out of use. Shared and unique
pointers use different methods to determine when to
free their pointed-to resource.

### The unique pointer
A unique pointer should be used when the pointer will
always be owned by one object and one object only.

```c++
class Child
{
    unique_ptr<TeddyBear> my_teddy_bear;
};
```

When the unique pointer falls out of scope, or its
parent object is destructed, the resource it is
pointing to will be freed automatically.


### The shared pointer
A shared pointer should be used when the contained object
might be passed around to other objects. Those objects
might want to extend the lifetime of the pointer so that
they don't operate on freed memory.

```c++
class Game
{
public:
    vector<shared_ptr<Player>> online_players;
};

// ... and off in another world

class Team
{
public:
    vector<shared_ptr<Player>> players;
};
```

In the above example, the Game object owns the players,
but a game might have a list of players on a team. Now
imagine if the player leaves the game and the game
object forgets about the player. The team class might need
to use the player object as part of it's cleanup procedure.
But since the pointer has been freed already by the Game
class, heap corruption will occur.

However, since we're using shared pointers, this won't
happen. Both classes own the same Player pointer, and
it will never be freed until the very last object releases
it.

This is still dangerous, however - as it could greatly
extend the object lifetime, causing increased memory usage.

This is why we have...

## The weak pointer
The weak pointer is a derivative of the shared pointer,
but is not optional; it is absolutely essential in the
objective of keeping object lifetime to a reasonable
length.

A weak pointer is a "shared pointer" (except not) that
does NOT increase the reference count on a shared pointer.

That means that this code:

```c++
auto a = std::make_shared<Car>();
weak_ptr b = a;
```

... results in `a` variable only having ONE reference.

However, a weak pointer acts like a door. We can open the
weak pointer to actually access the resources it represents.

```c++
auto a = std::make_shared<Car>();
weak_ptr b = a;
auto c = b.lock();
```

At the end of this code, the variable `a` actually has TWO
references instead of just one, and the type of `c` is
`shared_ptr<Car>` which points to a.

So while b itself does nothing, it can be used to access `a`
and to extend the lifetime of `a` until you're done with it!

Weak pointers are NOT optional. They are very important to
eliminate shared pointers that keep each other alive. If you
ever need a reference to something, but do not want to extend
its lifetime indefinitely, use a weak pointer instead of a
shared pointer.

In my experience, when choosing between a shared pointer and
a weak pointer, I ask myself this: "which object should take
*ownership* of the pointer, and which object just wants to
*reference* the pointer from time to time?"

If you are going to take *ownership*, use a shared pointer.
If you just need a *reference* to the resource, go with a
weak pointer. A hanging shared pointer could cause serious
headaches!