#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Wed Feb 8 14:44:33 2023
Based on: https://www.kaggle.com/datasets/arbazmohammad/world-airports-and-airlines-datasets
Sample input: --AIRLINES="airlines.yaml" --AIRPORTS="airports.yaml" --ROUTES="routes.yaml" --QUESTION="q1" --GRAPH_TYPE="bar"
@author: rivera
@author: doyeniyi 
""" 
import sys
import yaml
import pandas as pd
import matplotlib.pyplot as plt

def question1(airline_df: pd.DataFrame, airports_df: pd.DataFrame, routes_df: pd.DataFrame, question: str, graph_type: str) -> None:
    '''
    merges input data frames in order to obtain a data frame containing the top 20 airlines that offer the greatest number 
    of routes with destination country as Canada

    param airline_df: dataframe containing formation on airlines
    param airport_df: dataframe containing information on airports
    param routes_df: dataframe containing formation on routes
    param question: string the specifies what question this program has to answers
    param graph_type: string the specifies what graph type the pdf file created should show
    return: the program passes the final data frame to another function thus returns nothing
    '''
    airline_df.drop(['airline_country'], inplace=True, axis=1)
    airports_df.drop(['airport_name', 'airport_city', 'airport_icao_unique_code', 'airport_altitude'], inplace=True, axis=1)
    routes_df.drop(['route_from_aiport_id'], inplace=True, axis=1)

    airports_df = airports_df[airports_df['airport_country']=='Canada']

    routes_df = routes_df.rename(columns={'route_airline_id':'airline_id'})
    answer: pd.DataFrame = routes_df.merge(airline_df, on='airline_id', how='inner') 
    answer = answer.rename(columns={'route_to_airport_id':'airport_id'})
    answer = answer.merge(airports_df, on='airport_id', how='inner') 

    answer = df_lstrip(answer,answer.columns)
    answer = answer.groupby(['airline_name', 'airline_icao_unique_code'], as_index=False).size().sort_values(by=['size', 'airline_name'], ascending=[False, True]).head(20) 
    process_data(answer, question, graph_type) 
    
def question2(airline_df: pd.DataFrame, airports_df: pd.DataFrame, routes_df: pd.DataFrame, question: str, graph_type: str) -> None:
    '''
    merges input data frames in order to obtain a data frame containing the top 30 countries with least appearances as destination country on the routes data

    param airline_df: dataframe containing formation on airlines
    param airport_df: dataframe containing information on airports
    param routes_df: dataframe containing formation on routes
    param question: string the specifies what question this program has to answers
    param graph_type: string the specifies what graph type the pdf file created should show
    return: the program passes the final data frame to another function thus returns nothing
    '''
    airline_df.drop(['airline_country', 'airline_name', 'airline_icao_unique_code'], inplace=True, axis=1)
    airports_df.drop(['airport_name', 'airport_city', 'airport_icao_unique_code', 'airport_altitude'], inplace=True, axis=1)
    routes_df.drop(['route_from_aiport_id'], inplace=True, axis=1)

    routes_df = routes_df.rename(columns={'route_to_airport_id':'airport_id'})
    answer = routes_df.merge(airports_df, on='airport_id', how='inner') 

    answer = df_lstrip(answer,answer.columns)
    answer = answer.groupby(['airport_country'], as_index=False).size().sort_values(by=['size', 'airport_country']).head(30)
    process_data(answer, question, graph_type) 
     

def question3(airline_df: pd.DataFrame, airports_df: pd.DataFrame, routes_df: pd.DataFrame, question: str, graph_type: str) -> None:
    '''
    merges input data frames in order to obtain a data frame containing the top 10 destination airports

    param airline_df: dataframe containing formation on airlines
    param airport_df: dataframe containing information on airports
    param routes_df: dataframe containing formation on routes
    param question: string the specifies what question this program has to answers
    param graph_type: string the specifies what graph type the pdf file created should show
    return: the program passes the final data frame to another function thus returns nothing
    '''
    airline_df.drop(['airline_country', 'airline_name', 'airline_icao_unique_code'], inplace=True, axis=1)
    airports_df.drop(['airport_altitude'], inplace=True, axis=1)
    routes_df.drop(['route_from_aiport_id'], inplace=True, axis=1)
    
    routes_df = routes_df.rename(columns={'route_airline_id':'airline_id'})
    answer: pd.DataFrame = routes_df.merge(airline_df, on='airline_id', how='left') 
    answer = answer.rename(columns={'route_to_airport_id':'airport_id'})
    answer = answer.merge(airports_df, on='airport_id', how='left') 
    
    answer = df_lstrip(answer,answer.columns)
    answer = answer.groupby(['airport_name', 'airport_icao_unique_code', 'airport_city', 'airport_country'], as_index=False).size().sort_values(by=['size', 'airport_name'], ascending=[False, True]).head(10) 
    process_data(answer, question, graph_type) 

def question4(airports_df: pd.DataFrame, routes_df: pd.DataFrame, question: str, graph_type: str) -> None:
    '''
    merges input data frames in order to obtain a data frame containing the top 15 destination cities 

    param airport_df: dataframe containing information on airports
    param routes_df: dataframe containing formation on routes
    param question: string the specifies what question this program has to answers
    param graph_type: string the specifies what graph type the pdf file created should show
    return: the program passes the final data frame to another function thus returns nothing
    '''
    airports_df.drop(['airport_altitude', 'airport_icao_unique_code', 'airport_name'], inplace=True, axis=1)
    routes_df.drop(['route_from_aiport_id'], inplace=True, axis=1)

    airports_df = airports_df.rename(columns={'airport_id':'route_to_airport_id'})
    answer: pd.DataFrame = routes_df.merge(airports_df, on='route_to_airport_id', how='inner') 
    
    answer = df_lstrip(answer,answer.columns)
    answer = answer.groupby(['airport_city', 'airport_country'], as_index=False).size().sort_values(by=['size', 'airport_city'], ascending=[False, True]).head(15) 
    process_data(answer, question, graph_type) 

def question5(airline_df: pd.DataFrame, airports_df: pd.DataFrame, routes_df: pd.DataFrame, question: str, graph_type: str) -> None:
    '''
    merges input data frames in order to obtain a data frame containing the top 10 unique Canadian routes
    with the most distance between origin and destination altitudes

    param airline_df: dataframe containing formation on airlines
    param airport_df: dataframe containing information on airports
    param routes_df: dataframe containing formation on routes
    param question: string the specifies what question this program has to answers
    param graph_type: string the specifies what graph type the pdf file created should show
    return: the program passes the final data frame to another function thus returns nothing
    '''
    airline_df.drop(['airline_country', 'airline_name', 'airline_icao_unique_code'], inplace=True, axis=1)
    airports_df.drop(['airport_name', 'airport_city'], inplace=True, axis=1)
    
    airports_df = airports_df[airports_df['airport_country']=='Canada']

    airports_df = airports_df.rename(columns = {'airport_id':'route_to_airport_id'})
    answer: pd.DataFrame = routes_df.merge(airports_df, on='route_to_airport_id', how='inner')
    answer = answer.rename(columns = {'airport_altitude':'to_airport_altitude', 'airport_icao_unique_code':'to_airport_icao_unique_code'})

    airports_df = airports_df.rename(columns = {'route_to_airport_id': 'route_from_aiport_id'})
    answer = answer.merge(airports_df, on='route_from_aiport_id', how='inner')
    answer = answer.rename(columns = {'airport_altitude':'from_airport_altitude', 'airport_icao_unique_code':'from_airport_icao_unique_code'})

    answer['diff'] = -1.0               # creating a new column to store the difference and initializing it to -1 since the calculated difference >= 0
    answer = column_diff(answer, 'to_airport_altitude', 'from_airport_altitude', 'diff')
    answer = df_lstrip(answer,answer.columns)
    answer = answer.sort_values(by=['diff', 'to_airport_icao_unique_code', 'from_airport_icao_unique_code'], ascending=[False, True, True]) 
    process_data(answer, question, graph_type) 

def clear_duplicates(df: pd.DataFrame) -> tuple:
    '''
    stores unique routes from the data frame as a list of tuples
    
    param df: data frame containing information about the routes used in quesiton 5
    return: a list of tuples containing only the unique routes from the data frame
    '''
    uniques: tuple = []
    for index, row in df.iterrows(): 
        tmp1: tuple = (df.loc[index,'from_airport_icao_unique_code'], df.loc[index,'to_airport_icao_unique_code'], df.loc[index,'diff']) 
        tmp2: tuple = (df.loc[index,'to_airport_icao_unique_code'], df.loc[index,'from_airport_icao_unique_code'], df.loc[index,'diff']) 
        if tmp1 not in uniques and tmp2 not in uniques:
            uniques.append(tmp1) 
        
    return uniques
        
    
def column_diff(df: pd.DataFrame, in1: str, in2: str, out: str) -> pd.DataFrame:
    '''
    takes the difference between row values of two columns and stores it in the outpout column

    param df: the data frame that this function wants to modify
    param in1: string that spicifies the first column included in the calculation
    param in2: string that specifies the second column included in the calculation
    param out: string that specifies what column the resulting values should be stored in
    return: the updated data frame
    '''
    uniques: tuple = []
    for index, row in df.iterrows(): 
        df.loc[index,out] = abs(float(row[in1]) - float(row[in2]))   
    return df

    
def df_lstrip(df: pd.DataFrame, columns: str) -> pd.DataFrame: 
    '''
    strips the leading whitespace from all string entries in the data frame
    
    param df: the data frame that this function wants to modify
    param columns: a list of the column names in df
    return: the updated data frame 
    '''
    for index, row in df.iterrows(): 
        for column in columns:
            if type(df.loc[index,column]) == str:
                df.loc[index,column] = df.loc[index,column].lstrip()
    return df

def process_data(answer: pd.DataFrame, question: str, graph_type: str) -> None:
    '''
    takes information from the inputed data frame and creates a csv and pdf file based on the respective 
    question and graph_type passed in the command line

    param answer: the final dataframe passed by question1-question5
    param question: string the specifies what question this program has to answers
    param graph_type: string the specifies what graph type the pdf file created should show
    return: this function is the end of the program and thus returns nothing
    '''
    output_csv: file = open(f"{question}.csv",'w')
    keys: str = []
    values: int = [] 
    
    output_csv.write("subject,statistic\n")                     # writing to the csv file based on the question
    for index, row in answer.iterrows():
        if question == 'q1':
            keys.append(row['airline_name'])
            values.append(float(row['size']))
            output_csv.write(f"{row['airline_name']} ({row['airline_icao_unique_code']}),{row['size']}\n")
            
        elif question == 'q2':
            keys.append(row['airport_country'])
            values.append(float(row['size']))
            output_csv.write(f"{row['airport_country']},{row['size']}\n")

        elif question == 'q3':
            keys.append(f"{row['airport_name']} ({row['airport_icao_unique_code']})")
            values.append(float(row['size']))
            output_csv.write(f"\"{row['airport_name']} ({row['airport_icao_unique_code']}), {row['airport_city']}, {row['airport_country']}\",{row['size']}\n")

        elif question == 'q4':
            keys.append(f"{row['airport_city']}, {row['airport_country']}")
            values.append(float(row['size']))
            output_csv.write(f"\"{row['airport_city']}, {row['airport_country']}\",{row['size']}\n")

    if question == 'q5':                                      
        uniques = clear_duplicates(answer)                  # q5 is implemented differently than q1-q4 so it has its on individual case
        for i in range(10):
            keys.append(f"{uniques[i][0]}-{uniques[i][1]}")
            values.append(uniques[i][2])
            output_csv.write(f"{uniques[i][0]}-{uniques[i][1]},{uniques[i][2]}\n")
            
    f = plt.figure(figsize=(10,7))                          # creating the pie or bar chart based on the graph_type and saving it as a pdf file
    if graph_type == 'bar':
        plt.bar(keys, values)
        plt.tick_params(axis='x', which='major', labelsize=8)
        plt.xticks(rotation=60)
        plt.subplots_adjust(top=0.9, bottom=0.3)

    else:
        plt.pie(values, labels=keys, autopct='%1.0f%%', labeldistance=1.2, pctdistance=0.7)
        plt.subplots_adjust(left=0.1)

    if question == 'q1':
        plt.title("Top 20 Airlines With The Greatest Number Of Routes To Canada")
        if graph_type == 'bar':
            plt.xlabel("Airlines")
            plt.ylabel("Frequency")

    elif question == 'q2':
        plt.title("Top 30 Countries With The Least Appearances As A Destination Country")
        if graph_type == 'bar':
            plt.xlabel("Countries")
            plt.ylabel("Frequency")

    elif question == 'q3':
        plt.title("Top 10 Destination Airports")
        if graph_type == 'bar':
            plt.xlabel("Airports")
            plt.ylabel("Frequency")
        
    elif question == 'q4':
        plt.title("Top 15 Destination Cities")
        if graph_type == 'bar':
            plt.xlabel("Cities")
            plt.ylabel("Frequency")
        
    else:
        plt.title("Top 10 Canadian Routes With The Greatest Difference In Altitude")
        if graph_type == 'bar':
            plt.xlabel("Routes")
            plt.ylabel("Difference In Altitude")
        
    f.savefig(f"{question}.pdf")
    output_csv.close()

    
def main():
    airline: str = sys.argv[1].split('=')[1]                # extracting the command line arguments
    airports: str = sys.argv[2].split('=')[1]        
    routes: str = sys.argv[3].split('=')[1]
    question: str = sys.argv[4].split('=')[1]
    graph_type: str = sys.argv[5].split('=')[1]
    
    with open(airline) as f:                                                # creating dataframes for the respective files
        airline_df: pd.DataFrame = pd.DataFrame(yaml.load(f)['airlines'])

    with open(airports) as f:
        airports_df: pd.DataFrame = pd.DataFrame(yaml.load(f)['airports'])

    with open(routes) as f:
        routes_df: pd.DataFrame = pd.DataFrame(yaml.load(f)['routes'])
    
    if question == 'q1':
        question1(airline_df, airports_df, routes_df, question, graph_type)

    elif question == 'q2':
        question2(airline_df, airports_df, routes_df, question, graph_type)

    elif question == 'q3':
        question3(airline_df, airports_df, routes_df, question, graph_type)

    elif question == 'q4':
        question4(airports_df, routes_df, question, graph_type)

    else:
        question5(airline_df, airports_df, routes_df, question, graph_type)
        

if __name__ == '__main__':
    main()
