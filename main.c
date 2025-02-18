/*
   Copyright 2025 Birnadin Erick

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "core.c"

int main(void)
{
    puts("Finanz");
    /*
        Menu:
            - add expense
            - add income
            - calc holding

    */
    /*
     1. init ledger
     2. add records
     3. print the ledger
    */
    Ledger l;
    init_ledger(&l, "test", "948,00");
    add_record(&l, "rent", "360,00", SPENT);
    add_record(&l, "krankenversicherung", "139,41", SPENT);
    add_record(&l, "lebensmittel", "130,27", SPENT);
    add_record(&l, "minijob", "94,34", INCOME);

    print_ledger(&l);

    free_ledger(&l);
    exit(EXIT_SUCCESS);
}