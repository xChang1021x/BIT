#include<iostream>

using namespace std;

typedef struct Order{
	int orderid;
	int stockid;
	float price;
	int quantity;
	char mode;
	Order *next;
} ORDER; 

int main(){
	int x = 1;
	int orderId = 1;
	ORDER *headBuy = (ORDER*)malloc(sizeof(ORDER));
	ORDER *headSell = (ORDER*)malloc(sizeof(ORDER));
	headBuy->next = NULL;
	headSell->next = NULL;
	ORDER *p = NULL;
	while(x){
		scanf("%d", &x);
		
		if (x == 1){
			printf("orderid: %04d\n", orderId);
			ORDER *order = (ORDER*)malloc(sizeof(ORDER));
			scanf("%4d %f %d %c", &order->stockid, &order->price, &order->quantity, &order->mode);
			order->orderid = orderId;
			order->next = NULL;
			if (order->mode == 'b' || order->mode == 'B'){
				p = headSell;
				while (p->next != NULL){
					if (p->next->stockid == order->stockid && p->next->price <= order->price){
						printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (order->price + p->next->price)/2.0, min(p->next->quantity, order->quantity), orderId, p->next->orderid);
						int sold = min(p->next->quantity, order->quantity);
						p->next->quantity -= sold;
						order->quantity -= sold;
			
						if (p->next->quantity == 0){
							p->next = p->next->next;
						}
						if (order->quantity == 0){
							break;
						}
					}
					else p = p->next;
				}
				if (order->quantity != 0){
					p = headBuy;
					while (p->next != NULL && p->next->stockid != order->stockid){
						p = p->next;
					}
					if (p->next == NULL){
						p->next = order;
					}
					else if(p->next->price < order->price){
						order->next = p->next;
						p->next = order;
					}
					else{
						while (p->next != NULL && p->next->price >= order->price && p->next->stockid == order->stockid){
							p = p->next;
						}
						order->next = p->next;
						p->next = order;
					}				
				}
			}
			else if (order->mode == 's' || order->mode == 'S'){
				p = headBuy;
				while (p->next != NULL){
					if (p->next->stockid == order->stockid && p->next->price >= order->price){
						printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (order->price + p->next->price)/2.0, min(p->next->quantity, order->quantity), orderId, p->next->orderid);
						int sold = min(p->next->quantity, order->quantity);
						p->next->quantity -= sold;
						order->quantity -= sold;
						if (p->next->quantity == 0){
							p->next = p->next->next;
						}
						if (order->quantity == 0){
							break;
						}
					}
					else p = p->next;
				}
				if (order->quantity != 0){
					p = headSell;
					while (p->next != NULL && p->next->stockid != order->stockid){
						p = p->next;
					}
					if (p->next == NULL){
						p->next = order;
					}
					else if(p->next->price > order->price){
						order->next = p->next;
						p->next = order;
					}
					else{
						while (p->next != NULL && p->next->price <= order->price && p->next->stockid == order->stockid){
							p = p->next;
						}
						order->next = p->next;
						p->next = order;
					}				
				}
			}
			
			orderId++;
		}
		else if (x == 2){
			int search;
			scanf("%4d", &search);
			printf("buy orders:\n");
			p = headBuy->next;
			while (p != NULL){
				if (p->stockid == search){
					printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: b\n", p->orderid, p->stockid, p->price, p->quantity);
				}
				p = p->next;
			}
			printf("sell orders:\n");
			p = headSell->next;
			while (p != NULL){
				if (p->stockid == search){
					printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: s\n", p->orderid, p->stockid, p->price, p->quantity);
				}
				p = p->next;
			}
		}
		else if (x == 3){
			int search, flag = 1;
			scanf("%4d", &search);
			p = headBuy;
			while (p->next != NULL){
				if (p->next->orderid == search){
					printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: b\n", p->next->orderid, p->next->stockid, p->next->price, p->next->quantity);
					ORDER *deleteOrder = p->next;
					p->next = p->next->next;
					free(deleteOrder);
					flag = 0;
					break;
				}
				else p = p->next;
			}
			p = headSell;
			while (p->next != NULL){
				if (p->next->orderid == search){
					printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: s\n", p->next->orderid, p->next->stockid, p->next->price, p->next->quantity);
					ORDER *deleteOrder = p->next;
					p->next = p->next->next;
					free(deleteOrder);
					flag = 0;
					break;
				}
				else p = p->next;
			}
			if (flag){
				printf("not found\n");
			}
		}
	}
}