import streamlit as st
import numpy as np
import pandas as pd
import time


# Add text and data
st.title("My first app")

st.write("## Add text and data")
df = pd.DataFrame(
    {
        "first_column": [1, 2, 3, 4],
        "second column": [10, 20, 30, 40],
    }
)

st.write("Here is a table example:")
st.write(df)

# Use magic command
st.write("## Use magic")
st.write("Here is another table example with magic command:")
df

# Draw charts and maps
st.write("Draw charts and maps")
st.write("Draw a line chart:")
chart_data = pd.DataFrame(
    np.random.randn(20, 3),
    columns=["a", "b", "c"],
)
st.line_chart(chart_data)

st.write("Plot a map:")
map_data = pd.DataFrame(
    np.random.randn(1000, 2) / [50, 50] + [39.9, 116.4],
    columns=["latitude", "longitude"],
)
st.map(map_data)

# Add interactivity with widgets
st.write("## Add interactivity with widgets")
st.write("Use checkboxes to show/hide data:")
if st.checkbox("Show dataframe"):
    chart_data = pd.DataFrame(
        np.random.randn(20, 3),
        columns=["a", "b", "c"],
    )

    chart_data

st.write("Use a select box for options:")
option = st.selectbox("Which number do you like best?", df["first_column"])
"You selected: ", option

# Lay out your app
st.write("## Lay out your app")
st.write("Lay out app with sidebars:")
option = st.sidebar.selectbox(
    "Which number is your favorite? Select it in the sidebar.", df["first_column"]
)
"You selected: ", option

st.write("Use `st.columns`:")
left_column, right_column = st.columns(2)
pressed = left_column.button("Press me?")
if pressed:
    right_column.write("Woohoo!")

expander = st.expander("FAQ")
expander.write("Here you could put in some really, really long explanations...")

# Show progress
st.write("## Show progress")

"Start a long computation..."

# Add a placeholder
latest_iteration = st.empty()
bar = st.progress(0)
for i in range(100):
    # Update the progress bar with each iteration.
    latest_iteration.text(f"Iteration {i+1}")
    bar.progress(i + 1)
    time.sleep(0.1)

"...and now we're done!"
