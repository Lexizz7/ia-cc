#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

class Perceptron
{
public:
  std::vector<double> weights;
  double bias;
  double learning_rate;

  Perceptron(int n_inputs, double learning_rate)
  {
    this->learning_rate = learning_rate;
    for (int i = 0; i < n_inputs; i++)
    {
      this->weights.push_back(random_weight());
    }
    this->bias = random_weight();
  }

  double feed_forward(std::vector<bool> inputs)
  {
    double sum = 0;
    for (int i = 0; i < inputs.size(); i++)
    {
      if (inputs[i])
      {
        sum += this->weights[i];
      }
    }
    sum += this->bias;
    return activation_function(sum);
  }

  void train(std::vector<std::vector<bool>> inputs, std::vector<bool> outputs)
  {
    for (int i = 0; i < inputs.size(); i++)
    {
      double prediction = feed_forward(inputs[i]);
      double error = outputs[i] - prediction;
      for (int j = 0; j < this->weights.size(); j++)
      {
        if (inputs[i][j])
        {
          this->weights[j] += error * this->learning_rate;
        }
      }
      this->bias += error * this->learning_rate;
    }
  }

private:
  double random_weight()
  {
    return (double)rand() / RAND_MAX * 2 - 1;
  }

  double activation_function(double x)
  {
    return x > 0 ? 1 : 0;
  }
};

int main()
{
  srand(time(NULL));

  std::cout << "Escolha a função lógica:\n";
  std::cout << "1 - AND\n";
  std::cout << "2 - OR\n";
  std::cout << "3 - XOR\n";

  int function;
  std::cin >> function;

  if (function == 1 || function == 2 || function == 3)
  {
    std::cout << "Quantas entradas?";
    int n_inputs;
    std::cin >> n_inputs;

    if (n_inputs >= 1 && n_inputs <= 10)
    {
      Perceptron perceptron(n_inputs, 0.1);

      std::vector<std::vector<bool>> inputs;
      std::vector<bool> outputs;

      if (function == 1)
      {
        for (int i = 0; i < pow(2, n_inputs); i++)
        {
          std::vector<bool> input;
          for (int j = 0; j < n_inputs; j++)
          {
            input.push_back(i & (1 << j));
          }
          bool output = true;
          for (int j = 0; j < input.size(); j++)
          {
            if (!input[j])
            {
              output = false;
              break;
            }
          }
          inputs.push_back(input);
          outputs.push_back(output);
        }
      }
      else if (function == 2)
      {
        for (int i = 0; i < pow(2, n_inputs); i++)
        {
          std::vector<bool> input;
          for (int j = 0; j < n_inputs; j++)
          {
            input.push_back(i & (1 << j));
          }
          bool output = false;
          for (int j = 0; j < input.size(); j++)
          {
            if (input[j])
            {
              output = true;
              break;
            }
          }
          inputs.push_back(input);
          outputs.push_back(output);
        }
      }
      else if (function == 3)
      {
        for (int i = 0; i < pow(2, n_inputs); i++)
        {
          std::vector<bool> input;
          for (int j = 0; j < n_inputs; j++)
          {
            input.push_back(i & (1 << j));
          }
          bool output = false;
          for (int j = 0; j < input.size(); j++)
          {
            if (input[j])
            {
              output = !output;
            }
          }
          inputs.push_back(input);
          outputs.push_back(output);
        }
      }

      std::cout << "Treinando o Perceptron...\n";

      for (int i = 0; i < 10000; i++)
      {
        perceptron.train(inputs, outputs);
      }

      std::cout << "Testando o Perceptron com novos exemplos:\n";

      for (int i = 0; i < pow(2, n_inputs); i++)
      {
        std::vector<bool> input;
        for (int j = 0; j < n_inputs; j++)
        {
          input.push_back(i & (1 << j));
        }
        bool output = outputs[i];
        bool prediction = perceptron.feed_forward(input) > 0.5;
        std::cout << std::boolalpha << input[0];
        for (int j = 1; j < input.size(); j++)
        {
          std::cout << " " << input[j];
        }
        std::cout << " -> " << prediction << " (esperado " << output << ")\n";
      }
    }
    else
    {
      std::cout << "Número de entradas inválido.\n";
    }
  }
  else
  {
    std::cout << "Função lógica inválida.\n";
  }

  return 0;
}