# Vending-Machine-Simulation
Avishkar Hyperloop Controls Subsystem PS

Assumptions:
1) Functions for mechanical tasks like delivery of the product, return of change, acceptance of coins have not been implemented.
   Instead, if the machine outputs a success message for a certain task, we assume that the necessary processes have been carried out.
2) The Vending Machine's Menu has the following format:
        <index>  <item_name>  <quantity_available>  Rs.<price>
        

Pseudo-Code:
1) START
2) Assign CURRENT_STATE to be ST_MENU
3) Display Menu
4) Take order. (i.e, Take index number as input)
5) If index is invalid, display error message. goto 2).
6) Else if index is within the set of valid index numbers, Change CURRENT_STATE to ST_BILL.
      (i)    - Display bill. Accept Payment. If input is flag, display error message and goto 2).
      (ii)   - Compute balance as Price - Amount paid.
      (iii)  - If balance>0, update bill. goto 6)i).
      (iv)   - Else change CURRENT_STATE to ST_DELIVERY.
       (v)   - Return change and deliver product.
      (vi)   - Update quantity of the item.
      (vi)   - goto 2).
7) Else if index is password,
      (i)    - Change CURRENT_STATE to ST_MODIFY
      (ii)   - Take user's choice to ADD/DEL/MODIFY.
      (iii)  - If invalid choice, goto 2).
      (iv)   - Else, execute the task. and goto 2).
8) END
 
      


