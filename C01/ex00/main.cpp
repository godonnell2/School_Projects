#include "zombie.hpp"

int main() 
{
   
 Zombie	*my_zombie = NULL;

	my_zombie = my_zombie->newZombie("Foo");
	my_zombie->announce();
	my_zombie->randomChump("Bar");
	delete my_zombie;
	my_zombie = my_zombie->newZombie("Grace");
	my_zombie->announce();
	my_zombie->randomChump("evaluator");
	my_zombie->randomChump("Alexander the Great");
	delete my_zombie;
	return (0);
}

/*
Stack-based instantiation (Zombie z1)

The announce() method being called

z2 being destroyed automatically when going out of scope (you'll see its destructor message)
Stack Allocation (Zombie new_zombie(name);):
Objects created on the stack (local variables within a function) are automatically allocated when the function is entered and automatically destroyed (their destructors are called) as soon as the function exits or the variable goes out of scope. This is very efficient and automatic.
Heap Allocation (Zombie *new_zombie = new Zombie(name);):
Objects created on the heap (using new) are allocated in dynamic memory. Their memory is reserved until you explicitly delete them. If you don't delete them, they stay in memory until the program ends, leading to a memory leak. Their destruction is manual.
"Bar", "evaluator", and "Alexander the Great" are created on the stack inside their respective randomChump calls. They are destroyed immediately as soon as that randomChump function returns, which is why their destruction messages appear quickly after their announcements.
"Foo" and "Grace" are created on the heap by newZombie. Their destruction depends entirely on when you explicitly call delete on their pointers. In your code, you delete "Grace" after all the randomChump calls (and thus all the stack-allocated zombies) have completed their lifecycle. 
That's why "Grace is destroyed" is the very last zombie destruction message you see.
*/