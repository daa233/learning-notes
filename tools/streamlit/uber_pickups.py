import streamlit as st
import pandas as pd
import numpy as np


st.title("Uber pickups in NYC")

# Fetch some data
DATE_COLUMNS = "date/time"
DATA_URL = "https://s3-us-west-2.amazonaws.com/streamlit-demo-data/uber-raw-data-sep14.csv.gz"


# NOTE: Whenever you have a long-running computation in your code, consider refactoring it so
# you can use @st.cache, if possible.
@st.cache
def load_data(nrows):
    data = pd.read_csv(DATA_URL, nrows=nrows)
    data.rename(lambda x: str(x).lower(), axis="columns", inplace=True)
    data[DATE_COLUMNS] = pd.to_datetime(data[DATE_COLUMNS])
    return data


# Create a text element and let the reader know the data is loading
data_load_state = st.text("Loading data...")
# Load 10,000 rows of data into the dataframe
data = load_data(10000)
# Notify the reader that the data was successfully loaded
data_load_state.text("Done! (using st.cache)")

# Inspect the raw data
if st.checkbox("Show raw data"):
    st.subheader("Raw data")
    st.write(data)

# Draw a histogram
st.subheader("Nubmer of pickups by hour")
hist_values = np.histogram(data[DATE_COLUMNS].dt.hour, bins=24, range=(0, 24))[0]
st.bar_chart(hist_values)

# Plot data on a map
st.subheader("Map of all pickups")
st.map(data)

# Filter results with a slider
hour_to_filter = st.slider("hour", 0, 23, 17)  # min: 0h, max: 23h, default: 17h
filtered_data = data[data[DATE_COLUMNS].dt.hour == hour_to_filter]
st.subheader(f"Map of all pickups at {hour_to_filter}:00")
st.map(filtered_data)
