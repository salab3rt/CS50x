<h1>CS50x 2022 readability problem set</h1>

https://cs50.harvard.edu/x/2022/psets/2/readability/


Specification
Design and implement a program, readability, that computes the Coleman-Liau index of text.

Implement your program in a file called readability.c in a directory called readability.
<ul class="fa-ul">
  <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Implement your program in a file called <code class="language-plaintext highlighter-rouge">substitution.c</code> in a directory called <code class="language-plaintext highlighter-rouge">substitution</code>.</li>
  <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your program must accept a single command-line argument, the key to use for the substitution. The key itself should be case-insensitive, so whether any character in the key is uppercase or lowercase should not affect the behavior of your program.</li>
  <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error message of your choice (with <code class="language-plaintext highlighter-rouge">printf</code>) and return from <code class="language-plaintext highlighter-rouge">main</code> a value of <code class="language-plaintext highlighter-rouge">1</code> (which tends to signify an error) immediately.</li>
  <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>If the key is invalid (as by not containing 26 characters, containing any character that is not an alphabetic character, or not containing each letter exactly once), your program should print an error message of your choice (with <code class="language-plaintext highlighter-rouge">printf</code>) and return from <code class="language-plaintext highlighter-rouge">main</code> a value of <code class="language-plaintext highlighter-rouge">1</code> immediately.</li>
  <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your program must output <code class="language-plaintext highlighter-rouge">plaintext:</code> (without a newline) and then prompt the user for a <code class="language-plaintext highlighter-rouge">string</code> of plaintext (using <code class="language-plaintext highlighter-rouge">get_string</code>).</li>
  <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your program must output <code class="language-plaintext highlighter-rouge">ciphertext:</code> (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical character in the plaintext substituted for the corresponding character in the ciphertext; non-alphabetical characters should be outputted unchanged.</li>
  <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>Your program must preserve case: capitalized letters must remain capitalized letters; lowercase letters must remain lowercase letters.</li>
  <li data-marker="*"><span class="fa-li"><i class="fas fa-square"></i></span>After outputting ciphertext, you should print a newline. Your program should then exit by returning <code class="language-plaintext highlighter-rouge">0</code> from <code class="language-plaintext highlighter-rouge">main</code>.</li>
</ul>
