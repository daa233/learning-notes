## Installation

Install the conda virtual environment:
```bash
conda env create -f env.yml
```

Install the jupyter lab extensions:
```bash
jupyter labextension install @jupyter-voila/jupyterlab-preview
jupyter labextension install @jupyter-widgets/jupyterlab-manager
jupyter labextension install jupyterlab-plotly
jupyter labextension install plotlywidget
jupyter labextension install bqplot

jupyter lab build
```

## Serve command

```bash
voila learn-voila-demo.ipynb --no-browser --port 5000 --MappingKernelManager.cull_idle_timeout=6000 --VoilaConfiguration.file_whitelist="['.*']"
```
