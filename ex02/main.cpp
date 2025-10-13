/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:54:57 by cwolf             #+#    #+#             */
/*   Updated: 2025/10/13 13:45:00 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main (void)
{
    //Ford-Johnson-Algo
    //2 Parts: Merging & Inserting
    //Numbers: 25 24 23 22 21 20 19 18
    //Merging:
    //1. Split: 
    //Order 1: [25][24] [23][22] [21][20] [19][18] compare everytime 2 pairs > [24][25]   [22][23]  [20][21]  [18][19]
    //Order (*2) 2: ([24][25]) ([22][23]) ([20][21]) ([18][19]) > ([22][23])([24][25])  ([18][19])([20][21]) 
    //Order 4: ([22][23][24][25])  ([18][19][20][21]) > ([18][19][20][21]) ([22][23][24][25])
    //Order 8: only one pair left: ([18][19][20][21][22][23][24][25])



    
    //new example: Order 8:
    //[18, 19, 20, 21, 22, 23, 24, 25], [10, 11, 12, 13, 14, 15, 16, 17], [2, 3, 4, 5, 6, 7, 8, 9], [0, 1]
    // > 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1
    //Order 16 not possible to create 2 pairs (x)


    //2.Inserting
    // Inserting Order 8 (start)
    //With order 8 we create pairs (a1, b1, a2, ...) ???
    //a1(main) = [10, 11, 12, 13, 14, 15, 16, 17]   b1(main) = [18, 19, 20, 21, 22, 23, 24, 25]   a2(pend) = [2, 3, 4, 5, 6, 7, 8, 9] Leftover: [0,1]
    //sort a2 into main
    //compare EACH element of a2 with main and insert in right position 
    //After sorting: [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]. (Leftover smaller than elements in main, stays unsorted)
    
    //Order 4
    //a1 = [2, 3, 4, 5] b1 = [6, 7, 8, 9] a2 = [10, 11, 12, 13] b2 = [14, 15, 16, 17] a3 = [18, 19, 20, 21] b3 = [22, 23, 24, 25] Leftover
    //Main = a1, b1, a2, b2, Pend = a3 b3
    //sort all elements of pend into main: [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25] Leftover

    //Order 2
    //Create pairs of order size(2), Leftover size = pair size, sort Leftover in main
    //[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]

    //Finally Order 1 -> Each element is its own pair, list is sorted no further operations are required 


    
}