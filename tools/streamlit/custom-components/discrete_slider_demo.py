import streamlit as st
from discrete_slider.discrete_slider import discrete_silder


st.title("Custom Component: Discrete Silder")

# Create an instance of our component with a constant `options` arg, and
# print its output value.
options = ["a", "b", "c", "d"]
selected_value = discrete_silder(options=options)
# selected_value = st.slider(min_value=0, max_value=4, label="hello")
st.write(f"You selected: {selected_value}")
