# gtk-calculator (WIP)

- - - -

### Description

A simple calculator made in C with GTK4 and Libadwaita.

![Calculator](/calculator.png)

- - - -

### Building

1. Install cmake, git, gtk4, gtk4-devel, libadwaita and libadwaita-devel (will change depending on the distro you use,
   personally I use Fedora 36)

> sudo dnf install cmake git gtk4 gtk4-devel libadwaita libadwaita-devel

2. Go to your home directory

> cd ~

3. Clone this project

> git clone https://github.com/Vysp3r/gtk-calculator

4. Go to the cloned project directory

> cd gtk-calculator/

5. Generate cmake files

> cmake ~/gtk-calculator

6. Build the application

> cmake --build ~/gtk-calculator

7. Run the application

> ./GtkCalculator

8. Enjoy!

If you encounter any problems or have any requests, make sure
to [create an issue](https://github.com/Vysp3r/gtk-calculator/issues/new)!

- - - -

### Updates

> **Update 2.0.0**</br>
> I fully ported the project to use GTK4 and Libadwaita. I changed how the UI is displayed by using a .ui file instead
> of coding each component manually. All the buttons should now behave like they should except for the equal button.
> You can expect to have a basic version of the equal in the 2.1.0 update. I updated the README file to have the latest
> information. I changed the versioning of the project to allow me better flexibility concerning my updates which now
> means major, minor then patch.

> **Update 1.1.0**</br>
> You can now use the equal button, but it's really limited and will probably break in most cases as of right now. I
> will continue working on it to improve it, just be patient.

> **Update 1.0.0**</br>
> As of right now, the GUI and the buttons are working except the equal one. What that means is that right now you can
> enter your equation and erase it, but you cannot calculate it. I know it's weird, but it's coming soon, no worries.