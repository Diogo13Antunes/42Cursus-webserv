#!/usr/bin/python3

import sys

class Unbuffered(object):
   def __init__(self, stream):
       self.stream = stream
   def write(self, data):
       self.stream.write(data)
       self.stream.flush()
   def writelines(self, datas):
       self.stream.writelines(datas)
       self.stream.flush()
   def __getattr__(self, attr):
       return getattr(self.stream, attr)

sys.stdout = Unbuffered(sys.stdout)

content_length = 9

input_data = input()

nome_arquivo = "fromPython.txt"

# Abre o arquivo no modo de escrita ("w") e grava o input nele
with open(nome_arquivo, "w") as arquivo:
    arquivo.write(input_data)

htmlfile = "<!DOCTYPE html> <html> <body> "
htmlfile = htmlfile + " </body> </html>"
htmlfile += """
<p>
Bacon ipsum dolor amet pork belly beef ribs sirloin biltong, picanha jerky tongue shoulder kielbasa turducken shankle hamburger strip steak swine. Ham hock shank pastrami, turducken ground round biltong prosciutto. Biltong venison leberkas brisket picanha tri-tip turkey sirloin buffalo alcatra frankfurter rump bacon pork burgdoggen. Strip steak picanha filet mignon spare ribs flank doner cow kevin landjaeger pork loin ribeye brisket turducken corned beef. Meatloaf ball tip burgdoggen bacon ribeye short ribs corned beef tongue pork belly kevin fatback. Salami jerky corned beef filet mignon. Landjaeger beef tail shank.

Shankle ground round turkey, ham capicola turducken kevin chicken cupim. Pork swine filet mignon, biltong chislic hamburger sirloin burgdoggen. Turkey ribeye pancetta salami hamburger, ham hock short loin chislic bresaola bacon. Kevin jowl pork filet mignon, prosciutto bresaola short loin swine tri-tip pig fatback chicken andouille shoulder flank. Filet mignon capicola t-bone rump buffalo. Ball tip tenderloin tri-tip shoulder doner pastrami kielbasa chicken kevin. Bresaola prosciutto tongue kevin chuck beef ribs flank andouille meatball.

Ground round corned beef jerky biltong, pork chop landjaeger prosciutto spare ribs turducken pork belly pig short loin shankle. Corned beef ribeye burgdoggen biltong tongue ground round drumstick boudin sausage rump. Ribeye beef pork belly meatloaf, capicola bresaola salami filet mignon brisket buffalo. Chuck chislic beef ribs corned beef pork loin shoulder buffalo bresaola andouille doner meatball jerky ham hock shankle. Tongue sausage spare ribs, swine strip steak t-bone jerky meatball rump ribeye ham hock chuck bresaola chislic prosciutto. Jerky tongue kevin, prosciutto chislic ham swine drumstick.

Doner strip steak biltong capicola tenderloin brisket. Turducken biltong shankle pork belly spare ribs filet mignon bresaola swine jerky hamburger fatback. Ham hock tenderloin alcatra hamburger pig short loin jerky corned beef. Doner chuck alcatra, pork loin beef shank ham hock. Strip steak leberkas tri-tip ball tip tenderloin, biltong buffalo picanha tongue capicola.

Landjaeger bacon jowl shankle jerky rump, pancetta kevin pork loin porchetta prosciutto picanha pork chop. Jerky cupim shank pork, cow chuck hamburger pig landjaeger spare ribs swine leberkas. Porchetta picanha brisket, shank kevin corned beef biltong jowl chuck short loin beef capicola strip steak cupim shankle. Kielbasa turducken ground round ball tip filet mignon brisket shoulder venison alcatra meatloaf landjaeger burgdoggen shankle sausage jerky. Pig sirloin short ribs t-bone. Leberkas kevin pastrami, bresaola drumstick picanha tongue biltong ham ham hock venison.

Doner rump frankfurter t-bone tenderloin ham prosciutto ball tip leberkas tri-tip kevin ham hock kielbasa pork filet mignon. Sirloin short loin bacon spare ribs meatball doner jowl pastrami pork chop venison. Prosciutto drumstick ground round pig hamburger. Kevin drumstick doner filet mignon, frankfurter meatball rump tenderloin pancetta boudin jowl.

Short loin pork belly short ribs filet mignon pork shoulder tri-tip tenderloin hamburger. Bresaola drumstick doner shankle, andouille chicken pork belly flank kielbasa burgdoggen tongue jerky. Ball tip andouille chicken porchetta boudin flank, jerky shankle venison strip steak shank. Chuck kevin doner, meatball leberkas hamburger tri-tip ball tip ribeye. T-bone boudin jerky pig.

Porchetta beef ribs shankle rump meatloaf brisket shank tenderloin, kielbasa short ribs shoulder pork loin sirloin ground round. Ball tip kielbasa turducken picanha ham hock bresaola flank spare ribs meatloaf. Capicola ham hock flank t-bone meatloaf tail. Salami pork belly pork tenderloin chislic andouille fatback turkey brisket alcatra tongue kevin pig. Swine shank flank shankle corned beef beef ribs brisket frankfurter ground round salami venison picanha.
Bacon ipsum dolor amet pork belly beef ribs sirloin biltong, picanha jerky tongue shoulder kielbasa turducken shankle hamburger strip steak swine. Ham hock shank pastrami, turducken ground round biltong prosciutto. Biltong venison leberkas brisket picanha tri-tip turkey sirloin buffalo alcatra frankfurter rump bacon pork burgdoggen. Strip steak picanha filet mignon spare ribs flank doner cow kevin landjaeger pork loin ribeye brisket turducken corned beef. Meatloaf ball tip burgdoggen bacon ribeye short ribs corned beef tongue pork belly kevin fatback. Salami jerky corned beef filet mignon. Landjaeger beef tail shank.

Shankle ground round turkey, ham capicola turducken kevin chicken cupim. Pork swine filet mignon, biltong chislic hamburger sirloin burgdoggen. Turkey ribeye pancetta salami hamburger, ham hock short loin chislic bresaola bacon. Kevin jowl pork filet mignon, prosciutto bresaola short loin swine tri-tip pig fatback chicken andouille shoulder flank. Filet mignon capicola t-bone rump buffalo. Ball tip tenderloin tri-tip shoulder doner pastrami kielbasa chicken kevin. Bresaola prosciutto tongue kevin chuck beef ribs flank andouille meatball.

Ground round corned beef jerky biltong, pork chop landjaeger prosciutto spare ribs turducken pork belly pig short loin shankle. Corned beef ribeye burgdoggen biltong tongue ground round drumstick boudin sausage rump. Ribeye beef pork belly meatloaf, capicola bresaola salami filet mignon brisket buffalo. Chuck chislic beef ribs corned beef pork loin shoulder buffalo bresaola andouille doner meatball jerky ham hock shankle. Tongue sausage spare ribs, swine strip steak t-bone jerky meatball rump ribeye ham hock chuck bresaola chislic prosciutto. Jerky tongue kevin, prosciutto chislic ham swine drumstick.

Doner strip steak biltong capicola tenderloin brisket. Turducken biltong shankle pork belly spare ribs filet mignon bresaola swine jerky hamburger fatback. Ham hock tenderloin alcatra hamburger pig short loin jerky corned beef. Doner chuck alcatra, pork loin beef shank ham hock. Strip steak leberkas tri-tip ball tip tenderloin, biltong buffalo picanha tongue capicola.

Landjaeger bacon jowl shankle jerky rump, pancetta kevin pork loin porchetta prosciutto picanha pork chop. Jerky cupim shank pork, cow chuck hamburger pig landjaeger spare ribs swine leberkas. Porchetta picanha brisket, shank kevin corned beef biltong jowl chuck short loin beef capicola strip steak cupim shankle. Kielbasa turducken ground round ball tip filet mignon brisket shoulder venison alcatra meatloaf landjaeger burgdoggen shankle sausage jerky. Pig sirloin short ribs t-bone. Leberkas kevin pastrami, bresaola drumstick picanha tongue biltong ham ham hock venison.

Doner rump frankfurter t-bone tenderloin ham prosciutto ball tip leberkas tri-tip kevin ham hock kielbasa pork filet mignon. Sirloin short loin bacon spare ribs meatball doner jowl pastrami pork chop venison. Prosciutto drumstick ground round pig hamburger. Kevin drumstick doner filet mignon, frankfurter meatball rump tenderloin pancetta boudin jowl.

Short loin pork belly short ribs filet mignon pork shoulder tri-tip tenderloin hamburger. Bresaola drumstick doner shankle, andouille chicken pork belly flank kielbasa burgdoggen tongue jerky. Ball tip andouille chicken porchetta boudin flank, jerky shankle venison strip steak shank. Chuck kevin doner, meatball leberkas hamburger tri-tip ball tip ribeye. T-bone boudin jerky pig.

Porchetta beef ribs shankle rump meatloaf brisket shank tenderloin, kielbasa short ribs shoulder pork loin sirloin ground round. Ball tip kielbasa turducken picanha ham hock bresaola flank spare ribs meatloaf. Capicola ham hock flank t-bone meatloaf tail. Salami pork belly pork tenderloin chislic andouille fatback turkey brisket alcatra tongue kevin pig. Swine shank flank shankle corned beef beef ribs brisket frankfurter ground round salami venison picanha.
Bacon ipsum dolor amet pork belly beef ribs sirloin biltong, picanha jerky tongue shoulder kielbasa turducken shankle hamburger strip steak swine. Ham hock shank pastrami, turducken ground round biltong prosciutto. Biltong venison leberkas brisket picanha tri-tip turkey sirloin buffalo alcatra frankfurter rump bacon pork burgdoggen. Strip steak picanha filet mignon spare ribs flank doner cow kevin landjaeger pork loin ribeye brisket turducken corned beef. Meatloaf ball tip burgdoggen bacon ribeye short ribs corned beef tongue pork belly kevin fatback. Salami jerky corned beef filet mignon. Landjaeger beef tail shank.

Shankle ground round turkey, ham capicola turducken kevin chicken cupim. Pork swine filet mignon, biltong chislic hamburger sirloin burgdoggen. Turkey ribeye pancetta salami hamburger, ham hock short loin chislic bresaola bacon. Kevin jowl pork filet mignon, prosciutto bresaola short loin swine tri-tip pig fatback chicken andouille shoulder flank. Filet mignon capicola t-bone rump buffalo. Ball tip tenderloin tri-tip shoulder doner pastrami kielbasa chicken kevin. Bresaola prosciutto tongue kevin chuck beef ribs flank andouille meatball.

Ground round corned beef jerky biltong, pork chop landjaeger prosciutto spare ribs turducken pork belly pig short loin shankle. Corned beef ribeye burgdoggen biltong tongue ground round drumstick boudin sausage rump. Ribeye beef pork belly meatloaf, capicola bresaola salami filet mignon brisket buffalo. Chuck chislic beef ribs corned beef pork loin shoulder buffalo bresaola andouille doner meatball jerky ham hock shankle. Tongue sausage spare ribs, swine strip steak t-bone jerky meatball rump ribeye ham hock chuck bresaola chislic prosciutto. Jerky tongue kevin, prosciutto chislic ham swine drumstick.

Doner strip steak biltong capicola tenderloin brisket. Turducken biltong shankle pork belly spare ribs filet mignon bresaola swine jerky hamburger fatback. Ham hock tenderloin alcatra hamburger pig short loin jerky corned beef. Doner chuck alcatra, pork loin beef shank ham hock. Strip steak leberkas tri-tip ball tip tenderloin, biltong buffalo picanha tongue capicola.

Landjaeger bacon jowl shankle jerky rump, pancetta kevin pork loin porchetta prosciutto picanha pork chop. Jerky cupim shank pork, cow chuck hamburger pig landjaeger spare ribs swine leberkas. Porchetta picanha brisket, shank kevin corned beef biltong jowl chuck short loin beef capicola strip steak cupim shankle. Kielbasa turducken ground round ball tip filet mignon brisket shoulder venison alcatra meatloaf landjaeger burgdoggen shankle sausage jerky. Pig sirloin short ribs t-bone. Leberkas kevin pastrami, bresaola drumstick picanha tongue biltong ham ham hock venison.

Doner rump frankfurter t-bone tenderloin ham prosciutto ball tip leberkas tri-tip kevin ham hock kielbasa pork filet mignon. Sirloin short loin bacon spare ribs meatball doner jowl pastrami pork chop venison. Prosciutto drumstick ground round pig hamburger. Kevin drumstick doner filet mignon, frankfurter meatball rump tenderloin pancetta boudin jowl.

Short loin pork belly short ribs filet mignon pork shoulder tri-tip tenderloin hamburger. Bresaola drumstick doner shankle, andouille chicken pork belly flank kielbasa burgdoggen tongue jerky. Ball tip andouille chicken porchetta boudin flank, jerky shankle venison strip steak shank. Chuck kevin doner, meatball leberkas hamburger tri-tip ball tip ribeye. T-bone boudin jerky pig.

Porchetta beef ribs shankle rump meatloaf brisket shank tenderloin, kielbasa short ribs shoulder pork loin sirloin ground round. Ball tip kielbasa turducken picanha ham hock bresaola flank spare ribs meatloaf. Capicola ham hock flank t-bone meatloaf tail. Salami pork belly pork tenderloin chislic andouille fatback turkey brisket alcatra tongue kevin pig. Swine shank flank shankle corned beef beef ribs brisket frankfurter ground round salami venison picanha.
Bacon ipsum dolor amet pork belly beef ribs sirloin biltong, picanha jerky tongue shoulder kielbasa turducken shankle hamburger strip steak swine. Ham hock shank pastrami, turducken ground round biltong prosciutto. Biltong venison leberkas brisket picanha tri-tip turkey sirloin buffalo alcatra frankfurter rump bacon pork burgdoggen. Strip steak picanha filet mignon spare ribs flank doner cow kevin landjaeger pork loin ribeye brisket turducken corned beef. Meatloaf ball tip burgdoggen bacon ribeye short ribs corned beef tongue pork belly kevin fatback. Salami jerky corned beef filet mignon. Landjaeger beef tail shank.

Shankle ground round turkey, ham capicola turducken kevin chicken cupim. Pork swine filet mignon, biltong chislic hamburger sirloin burgdoggen. Turkey ribeye pancetta salami hamburger, ham hock short loin chislic bresaola bacon. Kevin jowl pork filet mignon, prosciutto bresaola short loin swine tri-tip pig fatback chicken andouille shoulder flank. Filet mignon capicola t-bone rump buffalo. Ball tip tenderloin tri-tip shoulder doner pastrami kielbasa chicken kevin. Bresaola prosciutto tongue kevin chuck beef ribs flank andouille meatball.

Ground round corned beef jerky biltong, pork chop landjaeger prosciutto spare ribs turducken pork belly pig short loin shankle. Corned beef ribeye burgdoggen biltong tongue ground round drumstick boudin sausage rump. Ribeye beef pork belly meatloaf, capicola bresaola salami filet mignon brisket buffalo. Chuck chislic beef ribs corned beef pork loin shoulder buffalo bresaola andouille doner meatball jerky ham hock shankle. Tongue sausage spare ribs, swine strip steak t-bone jerky meatball rump ribeye ham hock chuck bresaola chislic prosciutto. Jerky tongue kevin, prosciutto chislic ham swine drumstick.

Doner strip steak biltong capicola tenderloin brisket. Turducken biltong shankle pork belly spare ribs filet mignon bresaola swine jerky hamburger fatback. Ham hock tenderloin alcatra hamburger pig short loin jerky corned beef. Doner chuck alcatra, pork loin beef shank ham hock. Strip steak leberkas tri-tip ball tip tenderloin, biltong buffalo picanha tongue capicola.

Landjaeger bacon jowl shankle jerky rump, pancetta kevin pork loin porchetta prosciutto picanha pork chop. Jerky cupim shank pork, cow chuck hamburger pig landjaeger spare ribs swine leberkas. Porchetta picanha brisket, shank kevin corned beef biltong jowl chuck short loin beef capicola strip steak cupim shankle. Kielbasa turducken ground round ball tip filet mignon brisket shoulder venison alcatra meatloaf landjaeger burgdoggen shankle sausage jerky. Pig sirloin short ribs t-bone. Leberkas kevin pastrami, bresaola drumstick picanha tongue biltong ham ham hock venison.

Doner rump frankfurter t-bone tenderloin ham prosciutto ball tip leberkas tri-tip kevin ham hock kielbasa pork filet mignon. Sirloin short loin bacon spare ribs meatball doner jowl pastrami pork chop venison. Prosciutto drumstick ground round pig hamburger. Kevin drumstick doner filet mignon, frankfurter meatball rump tenderloin pancetta boudin jowl.

Short loin pork belly short ribs filet mignon pork shoulder tri-tip tenderloin hamburger. Bresaola drumstick doner shankle, andouille chicken pork belly flank kielbasa burgdoggen tongue jerky. Ball tip andouille chicken porchetta boudin flank, jerky shankle venison strip steak shank. Chuck kevin doner, meatball leberkas hamburger tri-tip ball tip ribeye. T-bone boudin jerky pig.

Porchetta beef ribs shankle rump meatloaf brisket shank tenderloin, kielbasa short ribs shoulder pork loin sirloin ground round. Ball tip kielbasa turducken picanha ham hock bresaola flank spare ribs meatloaf. Capicola ham hock flank t-bone meatloaf tail. Salami pork belly pork tenderloin chislic andouille fatback turkey brisket alcatra tongue kevin pig. Swine shank flank shankle corned beef beef ribs brisket frankfurter ground round salami venison picanha.
</p>

<h1> FIM DO HTML </h1>
"""

out = "Status: 200 OK\n"
out += "Server: webserv\n"
out += "Connection: keep-alive\n"
out += "Content-Length: " + str(len(htmlfile)) + "\n"
out += "Content-Type: " + "text/html" + "\n"
out += "\n"
out += htmlfile

print(out)
