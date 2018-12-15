int level()
{
    float result;
    int choice, num;
    printf("Press 1 to for easy\n");
    printf("Press 2 to for medium \n");
    printf("Press 3 to for hard\n");
    printf("Press 4 to for extremely hard\n");
    printf("Press 0 to for extremely easy \n");
    printf("Enter your choice:\n");
    scanf("%d",&choice);
    switch (choice) {
    case 1: {
        return 1;
    }
    case 2: {
        return 2;
    }
    case 3: {
        return 3;
    }
    case 0: {
        return 0;
    }

    default:
        printf("wrong Input\n");
    }
    return -1;
}
