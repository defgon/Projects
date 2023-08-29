import tkinter as tk
from tkinter import messagebox
import yahoo_fin.stock_info as yfin
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from tkinter import ttk
from tkinter import *
from yahoo_fin import options
from datetime import datetime, timedelta, date

start_date = datetime(1990, 1, 1) 
end_date = date.today() 

dates_list = []
while start_date <= datetime.combine(end_date, datetime.min.time()):
    date_str = start_date.strftime("%Y/%m/%d") 
    dates_list.append(date_str)
    start_date += timedelta(days=1) 

# text autocomplete
def autocomplete(list,box):
    current_text = box.get()
    matching_options = [option for option in list if option.startswith(current_text)]
    box['values'] = matching_options

#grafy
def graf(stock1,stock2,stock3,Option,start,end,period):
    if len(stock1) != 0 and len(stock2) == 0 and len(stock3) == 0:
        s1 = yfin.get_data(stock1,start_date = start,end_date = end,interval = period)
        plt.plot(s1[Option].index.strftime("%m-%d"),s1[Option].values,label = stock1)
        if(len(s1[Option].index) <= 30 and len(s1[Option].index) > 15):
            plt.xticks(s1[Option].index[::3].strftime("%m-%d"),rotation=45, ha='right')
        elif(len(s1[Option].index) > 30 and len(s1[Option].index) <= 90):
            plt.xticks(s1[Option].index[::6].strftime("%m-%d"),rotation=45, ha='right')
        elif(len(s1[Option].index) > 90 and len(s1[Option].index) <= 182):
            plt.xticks(s1[Option].index[::15].strftime("%m-%d"),rotation=45, ha='right')
        elif(len(s1[Option].index) > 182 and len(s1[Option].index) <= 365):
            plt.xticks(s1[Option].index[::40].strftime("%m-%d"),rotation=45, ha='right')

    elif len(stock1) != 0 and len(stock2) != 0 and len(stock3) == 0:
        s1 = yfin.get_data(stock1,start_date = start,end_date = end,interval = period)
        s2 = yfin.get_data(stock2,start_date = start,end_date = end,interval = period)
        plt.plot(s1[Option].index.strftime("%m-%d"),s1[Option].values,label = stock1)
        plt.plot(s2[Option].index.strftime("%m-%d"),s2[Option].values,label = stock1)
        if(len(s1[Option].index) <= 30 and len(s1[Option].index) > 15):
            plt.xticks(s1[Option].index[::3].strftime("%m-%d"),rotation=45, ha='right')
        elif(len(s1[Option].index) > 30 and len(s1[Option].index) <= 90):
            plt.xticks(s1[Option].index[::6].strftime("%m-%d"),rotation=45, ha='right')
        elif(len(s1[Option].index) > 90 and len(s1[Option].index) <= 182):
            plt.xticks(s1[Option].index[::15].strftime("%m-%d"),rotation=45, ha='right')
        elif(len(s1[Option].index) > 182 and len(s1[Option].index) <= 365):
            plt.xticks(s1[Option].index[::40].strftime("%m-%d"),rotation=45, ha='right')
    else:
        s1 = yfin.get_data(stock1,start_date = start,end_date = end,interval = period)
        s2 = yfin.get_data(stock2,start_date = start,end_date = end,interval = period)
        s3 = yfin.get_data(stock3,start_date = start,end_date = end,interval = period)
        plt.plot(s1[Option].index.strftime("%m-%d"),s1[Option].values,label = stock1)
        plt.plot(s2[Option].index.strftime("%m-%d"),s2[Option].values,label = stock2)
        plt.plot(s3[Option].index.strftime("%m-%d"),s3[Option].values,label = stock3)
        if(len(s1[Option].index) <= 30 and len(s1[Option].index) > 15):
            plt.xticks(s1[Option].index[::3].strftime("%m-%d"),rotation=45, ha='right')
        elif(len(s1[Option].index) > 30 and len(s1[Option].index) <= 90):
            plt.xticks(s1[Option].index[::6].strftime("%m-%d"),rotation=45, ha='right')
        elif(len(s1[Option].index) > 90 and len(s1[Option].index) <= 182):
            plt.xticks(s1[Option].index[::15].strftime("%m-%d"),rotation=45, ha='right')
        elif(len(s1[Option].index) > 182 and len(s1[Option].index) <= 365):
            plt.xticks(s1[Option].index[::40].strftime("%m-%d"),rotation=45, ha='right')
        
    plt.ylabel("[Price]")
    plt.xlabel("[Date]")
    plt.legend()
    plt.title("Graph of selected stocks")
    plt.show()

def grafMin(stock1,stock2,stock3,Option,start,end,period):
    if len(stock1) != 0 and len(stock2) == 0 and len(stock3) == 0:
        axis2X = [stock1]
        s1 = yfin.get_data(stock1,start_date = start,end_date = end,interval = period)
        min1 = min(s1[Option].values)
        axis2Y = [min1]
    elif len(stock1) != 0 and len(stock2) != 0 and len(stock3) == 0:
        axis2X = [stock1,stock2]
        s1 = yfin.get_data(stock1,start_date = start,end_date = end,interval = period)
        s2 = yfin.get_data(stock2,start_date = start,end_date = end,interval = period)
        min1 = min(s1[Option].values)
        min2 = min(s2[Option].values)
        axis2Y = [min1,min2]
    elif len(stock1) != 0 and len(stock2) != 0 and len(stock3) != 0:
        axis2X = [stock1,stock2,stock3]
        s1 = yfin.get_data(stock1,start_date = start,end_date = end,interval = period)
        s2 = yfin.get_data(stock2,start_date = start,end_date = end,interval = period)
        s3 = yfin.get_data(stock2,start_date = start,end_date = end,interval = period)
        min1 = min(s1[Option].values)
        min2 = min(s2[Option].values)
        min3 = min(s3[Option].values)
        axis2Y = [min1,min2,min3]    
    
    bar1 = plt.bar(axis2X,axis2Y,width = 0.4)
    plt.ylabel("[Price]")
    plt.xlabel("[Stock]")
    plt.yscale('log')
    plt.title("Graph of Min prices selected stocks")
    plt.bar_label(bar1)
    plt.show()

def grafMax(stock1,stock2,stock3,Option,start,end,period):
    if len(stock1) != 0 and len(stock2) == 0 and len(stock3) == 0:
        axis2X = [stock1]
        s1 = yfin.get_data(stock1,start_date = start,end_date = end,interval = period)
        max1 = max(s1[Option].values)
        axis2Y = [max1]
    elif len(stock1) != 0 and len(stock2) != 0 and len(stock3) == 0:
        axis2X = [stock1,stock2]
        s1 = yfin.get_data(stock1,start_date = start,end_date = end,interval = period)
        s2 = yfin.get_data(stock2,start_date = start,end_date = end,interval = period)
        max1 = max(s1[Option].values)
        max2 = max(s2[Option].values)
        axis2Y = [max1,max2]
    elif len(stock1) != 0 and len(stock2) != 0 and len(stock3) != 0:
        axis2X = [stock1,stock2,stock3]
        s1 = yfin.get_data(stock1,start_date = start,end_date = end,interval = period)
        s2 = yfin.get_data(stock2,start_date = start,end_date = end,interval = period)
        s3 = yfin.get_data(stock2,start_date = start,end_date = end,interval = period)
        max1 = max(s1[Option].values)
        max2 = max(s2[Option].values)
        max3 = max(s3[Option].values)
        axis2Y = [max1,max2,max3]    
    
    bar1 = plt.bar(axis2X,axis2Y,width = 0.4)
    plt.ylabel("[Price]")
    plt.xlabel("[Stock]")
    plt.yscale('log')
    plt.title("Graph of Max prices selected stocks")
    plt.bar_label(bar1)
    plt.show()


# gather stock symbols from major US exchanges
df1 = pd.DataFrame( yfin.tickers_sp500() )
df2 = pd.DataFrame( yfin.tickers_nasdaq() )
df3 = pd.DataFrame( yfin.tickers_dow() )
df4 = pd.DataFrame( yfin.tickers_other() )
# convert DataFrame to list, then to sets
sym1 = set( symbol for symbol in df1[0].values.tolist() )
sym2 = set( symbol for symbol in df2[0].values.tolist() )
sym3 = set( symbol for symbol in df3[0].values.tolist() )
sym4 = set( symbol for symbol in df4[0].values.tolist() )

def make(stock1,stock2,stock3,fromDate,toDate,PriceOption,GraphOption,Period):
    if GraphOption == "Maximum Price":
        grafMax(stock1,stock2,stock3,PriceOption,fromDate,toDate,Period)
    elif GraphOption == "Minimum Price":
        grafMin(stock1,stock2,stock3,PriceOption,fromDate,toDate,Period)
    else:
        date1 = datetime.strptime(fromDate, "%Y/%m/%d")
        date2 = datetime.strptime(toDate, "%Y/%m/%d")
        delta = (date2 - date1).days
        if delta > 365:
            messagebox.showerror("Error", "Can not plot more than year of data")
            return
        else:
            graf(stock1,stock2,stock3,PriceOption,fromDate,toDate,Period)

    if len(stock1) != 0 and len(stock2) == 0 and len(stock3) == 0:
        s1 = yfin.get_data(stock1,start_date = fromDate,end_date = toDate,interval = Period)
        median_B = s1[PriceOption].median()
        s1 = s1.describe()
        max_B = s1.loc['max', PriceOption]
        min_B = s1.loc['min', PriceOption]
        mean_B = s1.loc['mean', PriceOption]

        Max1.config(text="Max: %d" % max_B)
        Min1.config(text="Min: %d" % min_B)
        Mean1.config(text="Mean: %d" % mean_B)
        Median1.config(text="Median: %d" % median_B)
    elif len(stock1) != 0 and len(stock2) != 0 and len(stock3) == 0:
        s1 = yfin.get_data(stock1,start_date = fromDate,end_date = toDate,interval = Period)
        s2 = yfin.get_data(stock2,start_date = fromDate,end_date = toDate,interval = Period)
        median_B1 = s1[PriceOption].median()
        median_B2 = s2[PriceOption].median()

        s1 = s1.describe()
        s2 = s2.describe()

        max_B1 = s1.loc['max', PriceOption]
        min_B1 = s1.loc['min', PriceOption]
        mean_B1 = s1.loc['mean', PriceOption]

        max_B2 = s2.loc['max', PriceOption]
        min_B2 = s2.loc['min', PriceOption]
        mean_B2 = s2.loc['mean', PriceOption]

        Max1.config(text="Max: %d" % max_B1)
        Min1.config(text="Min: %d" % min_B1)
        Mean1.config(text="Mean: %d" % mean_B1)
        Median1.config(text="Median: %d" % median_B1)

        Max2.config(text="Max: %d" % max_B2)
        Min2.config(text="Min: %d" % min_B2)
        Mean2.config(text="Mean: %d" % mean_B2)
        Median2.config(text="Median: %d" % median_B2)
    elif len(stock1) != 0 and len(stock2) != 0 and len(stock3) != 0:
        s1 = yfin.get_data(stock1,start_date = fromDate,end_date = toDate,interval = Period)
        s2 = yfin.get_data(stock2,start_date = fromDate,end_date = toDate,interval = Period)
        s3 = yfin.get_data(stock2,start_date = fromDate,end_date = toDate,interval = Period)
        median_B1 = s1[PriceOption].median()
        median_B2 = s2[PriceOption].median()
        median_B3 = s3[PriceOption].median()

        s1 = s1.describe()
        s2 = s2.describe()
        s3 = s3.describe()

        max_B1 = s1.loc['max', PriceOption]
        min_B1 = s1.loc['min', PriceOption]
        mean_B1 = s1.loc['mean', PriceOption]

        max_B2 = s2.loc['max', PriceOption]
        min_B2 = s2.loc['min', PriceOption]
        mean_B2 = s2.loc['mean', PriceOption]

        max_B3 = s3.loc['max', PriceOption]
        min_B3 = s3.loc['min', PriceOption]
        mean_B3 = s3.loc['mean', PriceOption]

        Max1.config(text="Max: %d" % max_B1)
        Min1.config(text="Min: %d" % min_B1)
        Mean1.config(text="Mean: %d" % mean_B1)
        Median1.config(text="Median: %d" % median_B1)

        Max2.config(text="Max: %d" % max_B2)
        Min2.config(text="Min: %d" % min_B2)
        Mean2.config(text="Mean: %d" % mean_B2)
        Median2.config(text="Median: %d" % median_B2)

        Max3.config(text="Max: %d" % max_B3)
        Min3.config(text="Min: %d" % min_B3)
        Mean3.config(text="Mean: %d" % mean_B3)
        Median3.config(text="Median: %d" % median_B3)
        
        
# join the 4 sets into one. Because it's a set, there will be no duplicate symbols
symbols = set.union( sym1, sym2, sym3, sym4 )


# make gui
root = tk.Tk()
root.title("Stock Graph Maker")
root.geometry("800x400")

# Create a frame for the left side
left_frame = tk.Frame(root)
left_frame.pack(side=tk.LEFT, padx=20)

# Create comboboxs for stocks
Stock1Text = tk.Label(left_frame, text="Enter Stock1:")
Stock1Text.grid(row=0, column=0, pady=10)
Stock1 = ttk.Combobox(left_frame, values=[],width=18)
Stock1.grid(row=0, column=1, pady=10)

Stock2Text = tk.Label(left_frame, text="Enter Stock2:")
Stock2Text.grid(row=1, column=0, pady=10)
Stock2 = ttk.Combobox(left_frame, values=[],width=18)
Stock2.grid(row=1, column=1, pady=10)

Stock3Text = tk.Label(left_frame, text="Enter Stock3:")
Stock3Text.grid(row=2, column=0, pady=10)
Stock3 = ttk.Combobox(left_frame, values=[],width=18)
Stock3.grid(row=2, column=1, pady=10)

# Create comboboxs for dates
FromDateCbox = ttk.Combobox(left_frame, values=dates_list,width=18)
FromDateCbox.grid(row=3, column=0, padx=5, pady=10)

ToDateCbox = ttk.Combobox(left_frame, values=dates_list,width=18)
ToDateCbox.grid(row=3, column=1, padx=5, pady=10)

# Price options
PriceOptions = ["open", "high", "low","close","adjclose"]
PO = tk.StringVar(left_frame)
PO.set(PriceOptions[0])
PriceDD = tk.OptionMenu(left_frame, PO, *PriceOptions)
PriceDD.grid(row=4, column=0, padx=20, pady=10)

# Graph options
GraphOptions = ["Maximum Price", "Minimum Price", "Data plot"]
GO = tk.StringVar(left_frame)
GO.set(GraphOptions[0])
GraphDD = tk.OptionMenu(left_frame, GO, *GraphOptions)
GraphDD.grid(row=4, column=1, padx=20, pady=10)

# Period
PeriodText = tk.Label(left_frame, text="Select Period:")
PeriodText.grid(row=5, column=0, pady=10)
PeriodOptions = ["1d", "1wk", "1mo"]
PeO = tk.StringVar(left_frame)
PeO.set(PeriodOptions[0])
PeriodDD = tk.OptionMenu(left_frame, PeO, *PeriodOptions)
PeriodDD.grid(row=5, column=1, padx=20, pady=10)

# Plot button
Plot = tk.Button(left_frame,widt=40, text="Make Graph",
                command=lambda: make(Stock1.get(),Stock2.get(),Stock3.get(),
                FromDateCbox.get(),ToDateCbox.get(),PO.get(),GO.get(),PeO.get()))
Plot.grid(row=6,columnspan=3, padx=5, pady=20)


#Stock 1
Stock1Answer = tk.Label(left_frame, text="Stock1 data:")
Stock1Answer.grid(row=0, column=4,padx=40, pady=0)

Min1 = tk.Label(left_frame, text="Min:")
Min1.grid(row=0, column=5,padx=5, pady=0)

Max1 = tk.Label(left_frame, text="Max:")
Max1.grid(row=0, column=6,padx=10, pady=0)

Mean1 = tk.Label(left_frame, text="Mean:")
Mean1.grid(row=1, column=4,padx=40, pady=0)

Median1 = tk.Label(left_frame, text="Median:")
Median1.grid(row=1, column=5,padx=10, pady=0)

#Stock 2
Stock2Answer = tk.Label(left_frame, text="Stock2 data:")
Stock2Answer.grid(row=3, column=4,padx=40, pady=0)

Min2 = tk.Label(left_frame, text="Min:")
Min2.grid(row=3, column=5,padx=5, pady=0)

Max2 = tk.Label(left_frame, text="Max:")
Max2.grid(row=3, column=6,padx=10, pady=0)

Mean2 = tk.Label(left_frame, text="Mean:")
Mean2.grid(row=4, column=4,padx=40, pady=0)

Median2 = tk.Label(left_frame, text="Median:")
Median2.grid(row=4, column=5,padx=10, pady=0)

#Stock 3
Stock3Answer = tk.Label(left_frame, text="Stock3 data:")
Stock3Answer.grid(row=5, column=4,padx=40, pady=0)

Min3 = tk.Label(left_frame, text="Min:")
Min3.grid(row=5, column=5,padx=5, pady=0)

Max3 = tk.Label(left_frame, text="Max:")
Max3.grid(row=5, column=6,padx=10, pady=0)

Mean3 = tk.Label(left_frame, text="Mean:")
Mean3.grid(row=6, column=4,padx=40, pady=0)

Median3 = tk.Label(left_frame, text="Median:")
Median3.grid(row=6, column=5,padx=10, pady=0)


# bind dates
FromDateCbox.bind('<KeyRelease>', lambda event: autocomplete(dates_list,FromDateCbox))
ToDateCbox.bind('<KeyRelease>', lambda event: autocomplete(dates_list,ToDateCbox))

# bind stocks
Stock1.bind('<KeyRelease>', lambda event: autocomplete(symbols,Stock1))
Stock2.bind('<KeyRelease>', lambda event: autocomplete(symbols,Stock2))
Stock3.bind('<KeyRelease>', lambda event: autocomplete(symbols,Stock3))

root.mainloop()
