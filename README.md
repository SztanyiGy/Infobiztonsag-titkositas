Playfair cipher rövid magyarázata

A Playfair cipher egy klasszikus titkosítási módszer, amelyet a 19. században fejlesztettek ki. Az algoritmus különlegessége, hogy nem egyes betűket titkosít, hanem betűpárokat (digraphokat). Ez biztonságosabbá teszi, mint az egyszerűbb módszereket, például a Caesar cipher titkosítást.

A titkosítás egy 5×5-ös betűmátrix segítségével történik. A mátrixot egy kulcsszó alapján hozzuk létre. Először a kulcsszó betűi kerülnek a mátrixba ismétlés nélkül, majd az ábécé többi betűje következik. A mátrix 25 betűt tartalmaz, ezért általában az I és J betűt egynek tekintjük.

A titkosítandó szöveget először feldolgozzuk: minden betű nagybetű lesz, eltávolítjuk a nem betű karaktereket, majd a szöveget kétbetűs párokra bontjuk. Ha egy párban két azonos betű szerepel, közéjük egy X kerül. Ha a szöveg hossza páratlan, a végére szintén egy X kerül.

A titkosítás három szabály alapján történik:

Ha a két betű ugyanabban a sorban van a mátrixban, akkor a tőlük jobbra lévő betű lesz a titkosított pár.

Ha ugyanabban az oszlopban vannak, akkor az alattuk lévő betű lesz az eredmény.

Ha a betűk külön sorban és oszlopban vannak, akkor egy téglalapot alkotnak, és a betűk a téglalap másik sarkából kerülnek kiválasztásra.

A program ezeket a lépéseket automatikusan végrehajtja: létrehozza a kulcsból a mátrixot, előkészíti a szöveget, majd páronként alkalmazza a titkosítás szabályait, és kiírja a titkosított szöveget.
