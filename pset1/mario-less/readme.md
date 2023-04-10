<h1>CS50x 2022 mario-less</h1>

https://cs50.harvard.edu/x/2022/psets/1/mario/less/

Let’s recreate that pyramid in C, albeit in text, using hashes (#) for bricks, a la the below. Each hash is a bit taller than it is wide, so the pyramid itself will also be taller than it is wide.<br>
The program we’ll write will be called mario. And let’s allow the user to decide just how tall the pyramid should be by first prompting them for a positive integer between, say, 1 and 8, inclusive.
<pre class="highlight"><code>$ ./mario
Height: 8
       #
      ##
     ###
    ####
   #####
  ######
 #######
########
</code>
<code>$ ./mario
Height: 4
   #
  ##
 ###
####
</code>
</pre>
