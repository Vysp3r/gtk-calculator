# gtk-calculator
- - - -
### Description


A simple calculator made in C with GTK4.

![Calculator](/calculator.png)

- - - -
### Building
1. Install cmake, git, gtk4 and gtk4-devel (will change depending on the distro you use, personally I use Fedora 35)
>sudo dnf install cmake git gtk4 gtk4-devel
2. Go to your home directory
>cd ~
3. Clone this project 
>git clone https://github.com/Vysp3r/gtk-calculator
4. Go to the cloned project directory
>cd gtk-calculator/
5. Generate cmake files
>cmake ~/gtk-calculator
6. Build the application
>cmake --build ~/gtk-calculator
7. Run the application
>./GtkCalculator
8. Enjoy!

If you encounter any problems, make sure to [create an issue](https://github.com/Vysp3r/gtk-calculator/issues/new)!

- - - -
### Updates

>**Update 0.1**</br>
As of right now, the GUI and the buttons are working except the equal one.
What that means is that right now you can enter your equation and erase it, but you cannot calculate it. I know its weird, but it's coming soon, no worries.

>**Update 0.2**</br>
You can now use the equal button, but it's really limited and will probably break in most cases has of right now. I will continue working on it to improve it, just be patient.