#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

struct patient
{
    int id,age,dd,mm,yy;
    char name[20],guardian_name[20],disease_desc[300],address[300];
};

void addRecord(int);
void displayOne(int);
void displayAll();
void update(int);
void deleteOne(int);
void checkExist(int);
void deleteDb();
void renameDb();

char fname[]={"patient_records.dat"};

void main()
{
    int temp;
    while(1)
    {
    	FILE *fp;
    	struct patient p;
   		int ch,found=0;
    	fp=fopen(fname,"rb");
        printf("===================================| Patient Management System |==============================\n\n");
        printf("1)PATIENT         2)DOCTOR\nEnter your choice:");
        scanf("%d",&temp);
        if(temp==1){
        	printf("Enter patient ID: ");
        	scanf("%d",&temp);
        	checkExist(temp);
		}
		if(temp==2){
			while(1){
    			while(1){
    				fread(&p,sizeof(p),1,fp);
                	printf("1)view a patient details\n");
                	printf("2)view all patients details\n");
                	printf("3)Delete the whole patients database\n");
                	printf("4)Rename patients database file\n");
                	printf("0)exit\n\n");
                	printf("enter your choice: ");
                	scanf("%d",&ch);
                	switch(ch)
                	{
                    	case 1:printf("Enter a patient id:");
                    		   scanf("%d",&temp);
                    		   while(1){
                    		   	fread(&p,sizeof(p),1,fp);
        						if(p.id==temp){
        							printf("Record found:\n");
        							found=1;
        							displayOne(temp);
									break;
        						}
        						if(feof(fp) && found==0){
        							printf("Patient record not found\n");
        							break;
        					    }
							   }
							   break;

                    	case 2:displayAll();
                               break;

                    	case 3:deleteDb();
                               break;

                    	case 4:renameDb();
                               break;

                    	case 0:exit(0);
                    } 
    			}
    		fclose(fp);
			}
		}
        
    }
}

//search for the given id in db and create if its new else show options
void checkExist(int id)
{
    FILE *fp;
    struct patient p;
    int found=0,ch;
    fp=fopen(fname,"rb");
    while(1)
    {
        fread(&p,sizeof(p),1,fp);
        if(p.id==id)
        {
            found=1;
            while(1)
            {
                printf("\n1)Update record\n");
                printf("2)view your details\n");
                printf("3)Delete your record\n");
                printf("0)exit\n\n");
                printf("enter your choice: ");
                scanf("%d",&ch);
                switch(ch)
                {
                    case 1:update(id);
                           break;

                    case 2:displayOne(id);
                           break;
                           
                    case 3:deleteOne(id);
                            break;

                    case 0:exit(0);
                }
            }
            break;
        }
        if(feof(fp))
        {
            if(found==0){
            	printf("\nCreating new record\n");
                addRecord(id);
            }
        }
    }
    fclose(fp);
}

//add new record
void addRecord(int id)
{
    FILE *fp;
    struct patient p1;
    int ch,dd,mm,yy,x=0;
    fp=fopen(fname,"ab");
    p1.id=id;
    A:
    printf("\nEnter name:");
    scanf("%s",p1.name);
    printf("Enter age:");
    scanf("%d",&p1.age);
    printf("enter patient guardian name:");
    scanf("%s",&p1.guardian_name);
    printf("enter patient disease:");
    scanf("%s",&p1.disease_desc);
    X:
    printf("enter data(dd mm yyyy):");
    scanf("%d%d%d",&dd,&mm,&yy);
    if(yy>=1900 && yy<2023){
        if(mm>=1 && mm<=12){
            if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
            {
                p1.dd=dd;
                p1.mm=mm;
                p1.yy=yy;
                x=1;
            }
            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
               {
                p1.dd=dd;
                p1.mm=mm;
                p1.yy=yy;
                x=1;
               }
            else if((dd>=1 && dd<=28) && (mm==2))
                {
                p1.dd=dd;
                p1.mm=mm;
                p1.yy=yy;
                x=1;
                }
            else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0)))
                {
                p1.dd=dd;
                p1.mm=mm;
                p1.yy=yy;
                x=1;
                }
        }
    }
    if(x==0){
        printf("date is not valid");
        goto X;
    }
    printf("enter patient address:");
    scanf("%s",&p1.address);
    printf("\n");
    while(1)
    {
        printf("1)quit\n2)update records\n");
        printf("enter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:goto B;
                    break;

            case 2:goto A;
                    break;

            default:printf("please enter valid choice");
        }
    }
    B:
    fwrite(&p1,sizeof(p1),1,fp);
    fclose(fp);
    exit(0);
}

//display all patients records
void displayAll()
{
    FILE *fp;
    struct patient p;
    fp=fopen(fname,"rb");
    printf("\n========================================================\n\n");
    printf("\t\t All patients Details\n\n");
    printf("========================================================\n\n");
    printf("ID  Name  Age \tDisease\tGuardian\n\n");
    while(1)
    {
        fread(&p,sizeof(p),1,fp);
        if(feof(fp))
        {
            break;
        }
        printf("%d   %s  %d\t%s\t%s\n",p.id,p.name,p.age,p.disease_desc,p.guardian_name);
    }
    printf("========================================================\n\n");
    fclose(fp);
}

//modify
void update(int id)
{
    FILE *fp,*fp1;
    struct patient p,p1;
    int found=0,count=0;
    fp=fopen(fname,"rb");
    fp1=fopen("temp.dat","wb");
    while(1)
    {
        fread(&p,sizeof(p),1,fp);
        if(feof(fp))
        {
            break;
        }
        if(p.id==id)
        {
            found=1;
            fflush(stdin);
            printf("\nEnter patient Name:");
            scanf("%s",p.name);
            printf("Enter patient age:");
            scanf("%d",&p.age);
            printf("enter patient guardian name:");
            scanf("%s",&p.guardian_name);
            printf("enter patient disease:");
            scanf("%s",&p.disease_desc);
            //take date
            printf("enter patient address:");
            scanf("%s",&p.address);
            printf("\n========================================================\n\n");
            fwrite(&p,sizeof(p),1,fp1);
        }
        else
        {
            fwrite(&p,sizeof(p),1,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);

    if(found==0)
    {
        printf("Sorry No Record Found\n\n");
    }
    else
    {
        fp=fopen(fname,"wb");
        fp1=fopen("temp.dat","rb");

        while(1)
        {
            fread(&p,sizeof(p),1,fp1);
            if(feof(fp1))
            {
                break;
            }
        fwrite(&p,sizeof(p),1,fp);
        }
    }
    fclose(fp);
    fclose(fp1);
}

//rename db
void renameDb()
{
    char name[20];
    printf("\nEnter the New File Name:");
    fflush(stdin);
    scanf("%[^\n]",name);
    rename(fname,name);
    strcpy(fname,name);
}

//remove db
void deleteDb()
{
    FILE *fp,*fp1;
    struct patient p;

    char name[20];
    char val[20];

    printf("\nDo you want to make copy of it (Y/N):");
    scanf("%s",val);

    if(strcmp(val,"Y")==0)
    {
        printf("\nEnter the New File Name:");
        fflush(stdin);
        scanf("%[^\n]",name);

        fp=fopen(name,"wb");
        fp1=fopen(fname,"rb");

        while(1)
        {
            fread(&p,sizeof(p),1,fp1);
            if(feof(fp1))
            {
                break;
            }
            fwrite(&p,sizeof(p),1,fp);
        }
        fwrite("",0,0,fp1);
        fclose(fp);
        fclose(fp1);

        remove(fname);
        strcpy(fname,name);
    }
    else
    {
        fp=fopen(fname,"wb");
        fwrite("",0,0,fp);
        remove(fname);
    }
}

//delete your record
void deleteOne(int id)
{
    FILE *fp,*fp1;
    struct patient p,p1;
    int found=0,count=0;

    fp=fopen(fname,"rb");
    fp1=fopen("temp.dat","wb");

    while(1)
    {
        fread(&p,sizeof(p),1,fp);
        if(feof(fp))
        {
            break;
        }
        if(p.id==id)
        {
            found=1;
        }
        else
        {
            fwrite(&p,sizeof(p),1,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);

    if(found==0)
    {
        printf("Sorry No Record Found\n\n");
    }
    else
    {
    	printf("\nSuccessfully Deleted\n");
        fp=fopen(fname,"wb");
        fp1=fopen("temp.dat","rb");

        while(1)
        {
            fread(&p,sizeof(p),1,fp1);
            if(feof(fp1))
            {
                break;
            }
            fwrite(&p,sizeof(p),1,fp);
        }
    }
    fclose(fp);
    fclose(fp1);
}

//display a record
void displayOne
(int id)
{
    FILE *fp;
    struct patient p;
    int found=0;

    fp=fopen(fname,"rb");
    while(1)
    {
        fread(&p,sizeof(p),1,fp);

        if(feof(fp))
        {
            break;
        }
        if(p.id==id)
        {
            found=1;
            printf("\n========================================================\n\n");
            printf("\t\t patient Details \n\n");
            printf("========================================================\n\n");
            printf("ID  Name  Age\tDisease\tGuardian\n\n");
            printf("%d   %s  %d\t%s\t%s\n",p.id,p.name,p.age,p.disease_desc,p.guardian_name);
            printf("========================================================\n\n");
        }
    }
    if(found==0)
    {
        printf("\nSorry No Record Found\n");
    }
    fclose(fp);
}
