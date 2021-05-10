import numpy as np
import json
import Utils
# from Utils import Utils

# see https://towardsdatascience.com/lets-code-a-neural-network-in-plain-numpy-ae7e74410795
# see https://blog.zhaytam.com/2018/08/15/implement-neural-network-backpropagation/

def sigmoid(x):
	return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
	return x * (1 - x)

def tanh(x):
	return np.tanh(x)

def tanh_derivative(x):
	return 1 - x ** 2

def relu_derivative(x):
	x[x <= 0] = 0
	x[x > 0] = 1
	return x

def relu(Z):
    return np.maximum(0,Z)

def relu_backward(dA, Z):
    dZ = np.array(dA, copy = True)
    dZ[Z <= 0] = 0
    return dZ

def make_bias(n):
	# step = 0.1
	# van = step
	# tot = n * step
	# t = np.arange(van, tot + step / 10, step)
	# return np.ones(n)
	# return t

	return np.zeros(n)
	#return np.random.uniform(size = n)
	# return np.random.randn(n) * 0.1

def make_weights(n):
	# step = 0.1
	# van = step
	# tot = n[0] * n[1] * step
	# t = np.arange(van, tot + step / 10, step)
	# t = t.reshape(n)
	# return np.ones(n)
	# return t
	
	return np.random.randn(n[0], n[1]) * 0.1
	# return np.random.random((n[0], n[1]))

class Layer:

	def __init__(self, inn, n, af):
		"""
		:param int inn: the number of input nodes
		:param int n: the number of nodes in this layer
		"""
		self.input_nodes = inn
		self.nodes = n
		self.weights = make_weights((self.input_nodes, self.nodes))
		self.bias = make_bias((self.nodes))
		self.activation_funcname = af
		self.last_activation = None

	def activate(self, x):
		r = np.dot(x, self.weights) + self.bias
		# print(self.weights)
		if self.activation_funcname == "sigmoid":
			r = sigmoid(r)
		elif self.activation_funcname == "relu":
			r = relu(r)
		elif self.activation_funcname == "tanh":
			r = tanh(r)
		elif self.activation_funcname == "none":
			pass
		else:
			print("Unknown activation function: {}".format(self.activation_funcname))
		self.last_activation = r
		return self.last_activation

	def show(self):
		print("Layer: ", self.input_nodes, " -> ", self.nodes)
		print("Weights")
		print(self.weights)
		print("Bias")
		print(self.bias)
		print("Activation Function")
		print(self.activation_funcname)

	def mutate(self, rate):
		ff = np.vectorize(lambda x : ( x + np.random.normal(0, 0.1) if np.random.random() < rate else x))
		self.weights = ff(self.weights)
		#self.bias = ff(self.bias)

	def serialize(self):
		rb = np.round(self.bias, 3)
		rw = np.round(self.weights, 3)
		return {
			"input_nodes": self.input_nodes,
			"nodes": self.nodes,
			"activation_function": self.activation_funcname,
			"bias": rb.tolist(),
			"weights": rw.tolist()
		}

	@staticmethod
	def deserialize(data):
		layer = Layer(data["input_nodes"], data["nodes"], data["activation_function"])
		layer.last_activation = None
		layer.bias = np.array(data["bias"])
		layer.weights = np.array(data["weights"])
		# layer.show()
		return layer

	@staticmethod
	def crossover(l1, l2):
		s = l1.weights.shape
		for x in range(s[1]):
			for y in range(s[0] // 2):
				l1.weights[y][x], l2.weights[y][x] = l2.weights[y][x], l1.weights[y][x]

class NeuralNetwork:

	def __init__(self, inn, hl, hn, oun):
		"""
		:param int inn: the number of input nodes
		:param int hl: the number of hidden layers
		:param int hn: the number of nodes in each hidden layer
		:param int oun: the number of output nodes
		"""
		self.layers = []
		self.input_nodes = inn
		self.output_nodes = oun
		self.hidden_layers = hl
		self.hidden_nodes = hn

		self.add_layer(self.input_nodes, self.hidden_nodes, "sigmoid")
		for i in range(0, self.hidden_layers - 1):
			self.add_layer(self.hidden_nodes, self.hidden_nodes, "sigmoid")

		self.add_layer(self.hidden_nodes, self.output_nodes, "sigmoid") # sigmoid

		# for i in range(0, len(self.layers)):
		# 	self.layers[i].show()
		# input("A")

	def add_layer(self, inn, n, af):
		layer = Layer(inn, n, af)
		self.layers.append(layer)

	def feed_forward(self, x):
		for layer in self.layers:
			x = layer.activate(x)

		return x

	def predict(self, x):
		y = self.feed_forward(x)
		return y

	def backpropagation(self, x, y, learning_rate):
		output = self.feed_forward(x)
		for i in reversed(range(len(self.layers))):
			layer = self.layers[i]
			if layer == self.layers[-1]:
				layer.error = y - output
				layer.delta = layer.error * sigmoid_derivative(output)
			else:
				next_layer = self.layers[i + 1]
				layer.error = np.dot(next_layer.weights, next_layer.delta)
				layer.delta = layer.error * sigmoid_derivative(layer.last_activation)

		for i in range(len(self.layers)):
			layer = self.layers[i]
			input_to_use = np.atleast_2d(x if i == 0 else self.layers[i - 1].last_activation)
			layer.weights += layer.delta * input_to_use.T * learning_rate

	def train(self, X, y, learning_rate, max_epochs):
		"""
		Trains the neural network using backpropagation.
		:param X: The input values.
		:param y: The target values.
		:param float learning_rate: The learning rate (between 0 and 1).
		:param int max_epochs: The maximum number of epochs (cycles).
		:return: The list of calculated MSE errors.
		"""
		mses = []
		for i in range(max_epochs):
			for j in range(len(X)):
				self.backpropagation(X[j], y[j], learning_rate)
			if i % 10 == 0:
				mse = np.mean(np.square(y - self.feed_forward(X)))
				mses.append(mse)
				print('Epoch: #%s, MSE: %f' % (i, float(mse)))

		return mses

	def copy(self):
		new = NeuralNetwork(self.input_nodes, self.hidden_layers, self.hidden_nodes, self.output_nodes)
		for i in range(len(self.layers)):
			new.layers[i].weights = self.layers[i].weights.copy()
			new.layers[i].bias = self.layers[i].bias.copy()
			new.layers[i].activation_funcname = self.layers[i].activation_funcname
		return new

	def mutate(self, rate):
		for i in range(len(self.layers)):
			self.layers[i].mutate(rate);

	@staticmethod
	def crossover(nn1, nn2):
		b1 = nn1.copy()
		b2 = nn2.copy()

		for i in range(len(b1.layers)):
			Layer.crossover(b1.layers[i], b2.layers[i])

		return b1, b2

	def serialize(self):
		data = {}
		data["input_nodes"] = self.input_nodes
		data["output_nodes"] = self.output_nodes
		data["hidden_layers"] = self.hidden_layers
		data["hidden_nodes"] = self.hidden_nodes
		data["layers"] = []
		
		for i in range(len(self.layers)):
			data["layers"].append(self.layers[i].serialize())
		
		return json.dumps(data, indent = 2)

	@staticmethod
	def deserialize(jsonstring):
		data = json.loads(jsonstring)
		nn = NeuralNetwork(data["input_nodes"], data["hidden_layers"], data["hidden_nodes"], data["output_nodes"])
		nn.layers.clear()
		for p in data['layers']:
			layer = Layer.deserialize(p)
			nn.layers.append(layer)
		return nn

	#@staticmethod
	#def accuracy(y_pred, y_true):
	#	"""
	#	Calculates the accuracy between the predicted labels and true labels.
	#	:param y_pred: The predicted labels.
	#	:param y_true: The true labels.
	#	:return: The calculated accuracy.
	#	"""
	#	return (y_pred - y_true).mean()
